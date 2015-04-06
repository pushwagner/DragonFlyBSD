/*
 * Copyright (c) 2015 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@dragonflybsd.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * This module implements various PFS-based helper threads.
 */
#include "hammer2.h"

static int hammer2_sync_slaves(hammer2_syncthr_t *thr,
			hammer2_cluster_t *cparent, int *errors);
static void hammer2_update_pfs_status(hammer2_syncthr_t *thr,
			hammer2_cluster_t *cparent);
static int hammer2_sync_insert(hammer2_syncthr_t *thr,
			hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
			int i, int *errors);
static int hammer2_sync_destroy(hammer2_syncthr_t *thr,
			hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
			int i, int *errors);
static int hammer2_sync_replace(hammer2_syncthr_t *thr,
			hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
			int i, int *errors);

/*
 * Initialize the suspplied syncthr structure, starting the specified
 * thread.
 */
void
hammer2_syncthr_create(hammer2_syncthr_t *thr, hammer2_pfs_t *pmp,
		       void (*func)(void *arg))
{
	lockinit(&thr->lk, "h2syncthr", 0, 0);
	thr->pmp = pmp;
	lwkt_create(func, thr, &thr->td, NULL, 0, -1, "h2pfs");
}

/*
 * Terminate a syncthr.  This function will silently return if the syncthr
 * was never initialized or has already been deleted.
 *
 * This is accomplished by setting the STOP flag and waiting for the td
 * structure to become NULL.
 */
void
hammer2_syncthr_delete(hammer2_syncthr_t *thr)
{
	if (thr->td == NULL)
		return;
	lockmgr(&thr->lk, LK_EXCLUSIVE);
	atomic_set_int(&thr->flags, HAMMER2_SYNCTHR_STOP);
	wakeup(&thr->flags);
	while (thr->td) {
		lksleep(thr, &thr->lk, 0, "h2thr", hz);
	}
	lockmgr(&thr->lk, LK_RELEASE);
	thr->pmp = NULL;
	lockuninit(&thr->lk);
}

/*
 * Asynchronous remaster request.  Ask the synchronization thread to
 * start over soon (as if it were frozen and unfrozen, but without waiting).
 * The thread always recalculates mastership relationships when restarting.
 */
void
hammer2_syncthr_remaster(hammer2_syncthr_t *thr)
{
	if (thr->td == NULL)
		return;
	lockmgr(&thr->lk, LK_EXCLUSIVE);
	atomic_set_int(&thr->flags, HAMMER2_SYNCTHR_REMASTER);
	wakeup(&thr->flags);
	lockmgr(&thr->lk, LK_RELEASE);
}

void
hammer2_syncthr_freeze(hammer2_syncthr_t *thr)
{
	if (thr->td == NULL)
		return;
	lockmgr(&thr->lk, LK_EXCLUSIVE);
	atomic_set_int(&thr->flags, HAMMER2_SYNCTHR_FREEZE);
	wakeup(&thr->flags);
	while ((thr->flags & HAMMER2_SYNCTHR_FROZEN) == 0) {
		lksleep(thr, &thr->lk, 0, "h2frz", hz);
	}
	lockmgr(&thr->lk, LK_RELEASE);
}

void
hammer2_syncthr_unfreeze(hammer2_syncthr_t *thr)
{
	if (thr->td == NULL)
		return;
	lockmgr(&thr->lk, LK_EXCLUSIVE);
	atomic_clear_int(&thr->flags, HAMMER2_SYNCTHR_FROZEN);
	wakeup(&thr->flags);
	lockmgr(&thr->lk, LK_RELEASE);
}

/*
 * Primary management thread.
 *
 * On the SPMP - handles bulkfree and dedup operations
 * On a PFS    - handles remastering and synchronization
 */
void
hammer2_syncthr_primary(void *arg)
{
	hammer2_syncthr_t *thr = arg;
	hammer2_cluster_t *cparent;
	hammer2_pfs_t *pmp;
	int errors[HAMMER2_MAXCLUSTER];
	int error;

	pmp = thr->pmp;

	lockmgr(&thr->lk, LK_EXCLUSIVE);
	while ((thr->flags & HAMMER2_SYNCTHR_STOP) == 0) {
		/*
		 * Handle freeze request
		 */
		if (thr->flags & HAMMER2_SYNCTHR_FREEZE) {
			atomic_set_int(&thr->flags, HAMMER2_SYNCTHR_FROZEN);
			atomic_clear_int(&thr->flags, HAMMER2_SYNCTHR_FREEZE);
		}

		/*
		 * Force idle if frozen until unfrozen or stopped.
		 */
		if (thr->flags & HAMMER2_SYNCTHR_FROZEN) {
			lksleep(&thr->flags, &thr->lk, 0, "h2idle", 0);
			continue;
		}

		/*
		 * Reset state on REMASTER request
		 */
		if (thr->flags & HAMMER2_SYNCTHR_REMASTER) {
			atomic_clear_int(&thr->flags, HAMMER2_SYNCTHR_REMASTER);
			/* reset state */
		}

		/*
		 * Synchronization scan.
		 */
		hammer2_trans_init(&thr->trans, pmp, 0);
		cparent = hammer2_inode_lock(pmp->iroot,
					     HAMMER2_RESOLVE_ALWAYS);
		hammer2_update_pfs_status(thr, cparent);
		bzero(errors, sizeof(errors));
		error = hammer2_sync_slaves(thr, cparent, errors);
		if (error)
			kprintf("hammer2_sync_slaves: error %d\n", error);
		hammer2_inode_unlock(pmp->iroot, cparent);
		hammer2_trans_done(&thr->trans);

		/*
		 * Wait for event, or 5-second poll.
		 */
		lksleep(&thr->flags, &thr->lk, 0, "h2idle", hz * 5);
	}
	thr->td = NULL;
	wakeup(thr);
	lockmgr(&thr->lk, LK_RELEASE);
	/* thr structure can go invalid after this point */
}

/*
 * Given a locked cluster created from pmp->iroot, update the PFS's
 * reporting status.
 */
static
void
hammer2_update_pfs_status(hammer2_syncthr_t *thr, hammer2_cluster_t *cparent)
{
	hammer2_pfs_t *pmp = thr->pmp;
	uint32_t flags;

	flags = cparent->flags & HAMMER2_CLUSTER_ZFLAGS;
	if (pmp->flags == flags)
		return;
	pmp->flags = flags;

	kprintf("pfs %p", pmp);
	if (flags & HAMMER2_CLUSTER_MSYNCED)
		kprintf(" masters-all-good");
	if (flags & HAMMER2_CLUSTER_SSYNCED)
		kprintf(" slaves-all-good");

	if (flags & HAMMER2_CLUSTER_WRHARD)
		kprintf(" quorum/rw");
	else if (flags & HAMMER2_CLUSTER_RDHARD)
		kprintf(" quorum/ro");

	if (flags & HAMMER2_CLUSTER_UNHARD)
		kprintf(" out-of-sync-masters");
	else if (flags & HAMMER2_CLUSTER_NOHARD)
		kprintf(" no-masters-visible");

	if (flags & HAMMER2_CLUSTER_WRSOFT)
		kprintf(" soft/rw");
	else if (flags & HAMMER2_CLUSTER_RDSOFT)
		kprintf(" soft/ro");

	if (flags & HAMMER2_CLUSTER_UNSOFT)
		kprintf(" out-of-sync-slaves");
	else if (flags & HAMMER2_CLUSTER_NOSOFT)
		kprintf(" no-slaves-visible");
	kprintf("\n");
}

/*
 * TODO - have cparent use a shared lock normally instead of exclusive,
 *	  (needs to be upgraded for slave adjustments).
 */
static
int
hammer2_sync_slaves(hammer2_syncthr_t *thr, hammer2_cluster_t *cparent,
		    int *errors)
{
	hammer2_pfs_t *pmp;
	hammer2_cluster_t *cluster;
	hammer2_cluster_t *scluster;
	hammer2_chain_t *chain;
	hammer2_key_t key_next;
	int error;
	int nerror;
	int i;
	int n;
	int noslaves;

	pmp = thr->pmp;

	/*
	 * Nothing to do if all slaves are synchronized.
	 * Nothing to do if cluster not authoritatively readable.
	 */
	if (pmp->flags & HAMMER2_CLUSTER_SSYNCED) {
		kprintf("pfs %p: all slaves are synchronized\n", pmp);
		return(0);
	}
	if ((pmp->flags & HAMMER2_CLUSTER_RDHARD) == 0) {
		kprintf("pfs %p: slave sync waiting, cluster not available\n",
			pmp);
		return(HAMMER2_ERROR_INCOMPLETE);
	}
	kprintf("pfs %p: run synchronization\n", pmp);

	error = 0;

	/*
	 * XXX snapshot the source to provide a stable source to copy.
	 */

	/*
	 * Update all local slaves (remote slaves are handled by the sync
	 * threads on their respective hosts).
	 *
	 * Do a full topology scan, insert/delete elements on slaves as
	 * needed.  cparent must be ref'd so we can unlock and relock it
	 * on the recursion.
	 */
	hammer2_cluster_ref(cparent);
	cluster = hammer2_cluster_lookup(cparent, &key_next,
					 HAMMER2_KEY_MIN, HAMMER2_KEY_MAX,
					 HAMMER2_LOOKUP_NODATA |
					 HAMMER2_LOOKUP_NOLOCK);

	/*
	 * Ignore degenerate DIRECTDATA case for file inode
	 */
	kprintf("X1 %p %p\n", cluster, cparent);
	if (cluster == cparent) {
		hammer2_cluster_drop(cluster);
		cluster = NULL;
	}

	/*
	 * Scan elements
	 */
	while (cluster) {
		noslaves = 1;
		for (i = 0; i < cluster->nchains; ++i) {
			if (pmp->pfs_types[i] != HAMMER2_PFSTYPE_SLAVE)
				continue;
			chain = cluster->array[i].chain;

			/*
			 * Disable recursion for this index and loop up
			 * if a chain error is detected.
			 *
			 * A NULL chain is ok, it simply indicates that
			 * the slave reached the end of its scan, but we
			 * might have stuff from the master that still
			 * needs to be copied in.
			 */
			if (chain && chain->error) {
				kprintf("chain error index %d: %d\n", i, chain->error);
				errors[i] = chain->error;
				error = chain->error;
				cluster->array[i].flags |=
						HAMMER2_CITEM_INVALID;
				continue;
			}
			kprintf("chain index %d: %p\n", i, chain);

			noslaves = 0;

			/*
			 * Skip if the slave already has the record (everything
			 * matches including the mirror_tid).
			 *
			 * XXX also skip if parent is an indirect block and
			 *     is up-to-date.
			 */
			if (chain && (cluster->array[i].flags &
				      HAMMER2_CITEM_INVALID) == 0) {
				continue;
			}

			/*
			 * Otherwise adjust the slave.
			 */
			if (chain)
				n = hammer2_chain_cmp(cluster->focus, chain);
			else
				n = -1;	/* end-of-scan on slave */

			if (n < 0) {
				/*
				 * slave chain missing, create
				 */
				nerror = hammer2_sync_insert(thr,
							     cparent, cluster,
							     i, errors);
			} else if (n > 0) {
				/*
				 * excess slave chain, destroy
				 */
				nerror = hammer2_sync_destroy(thr,
							      cparent, cluster,
							      i, errors);
				hammer2_cluster_next_single_chain(
					cparent, cluster,
					&key_next,
					HAMMER2_KEY_MIN,
					HAMMER2_KEY_MAX,
					i,
					HAMMER2_LOOKUP_NODATA |
					HAMMER2_LOOKUP_NOLOCK);
				/*
				 * Re-execute same index, there might be more
				 * items to delete before this slave catches
				 * up to the focus.
				 */
				--i;
				continue;
			} else {
				/*
				 * key match but other things did not, replace.
				 */
				nerror = hammer2_sync_replace(thr,
							      cparent, cluster,
							      i, errors);
			}
			if (nerror)
				error = nerror;

			/*
			 * Recurse on inode.  Avoid unnecessarily blocking
			 * operations by temporarily unlocking the parent.
			 */
			if (cluster->focus->bref.type ==
			    HAMMER2_BREF_TYPE_INODE) {
				hammer2_cluster_unlock(cparent);
				scluster = hammer2_cluster_copy(cluster);
				hammer2_cluster_lock(scluster,
						     HAMMER2_RESOLVE_ALWAYS |
						     HAMMER2_RESOLVE_NOREF);
				nerror = hammer2_sync_slaves(thr, scluster,
							     errors);
				if (nerror)
					error = nerror;
				hammer2_cluster_unlock(scluster);
				/* XXX mirror_tid on scluster */
				/* flush needs to not update mirror_tid */
				hammer2_cluster_lock(cparent,
						     HAMMER2_RESOLVE_ALWAYS);
			}
		}
		if (noslaves) {
			kprintf("exhausted slaves\n");
			break;
		}
		cluster = hammer2_cluster_next(cparent, cluster,
					       &key_next,
					       HAMMER2_KEY_MIN,
					       HAMMER2_KEY_MAX,
					       HAMMER2_LOOKUP_NODATA |
					       HAMMER2_LOOKUP_NOLOCK);
	}
	hammer2_cluster_drop(cparent);
	if (cluster)
		hammer2_cluster_drop(cluster);

	return error;
}

/*
 * cparent is locked exclusively, with an extra ref, cluster is not locked.
 */
static
int
hammer2_sync_insert(hammer2_syncthr_t *thr,
		    hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
		    int i, int *errors)
{
	hammer2_chain_t *focus;
	hammer2_chain_t *chain;

	focus = cluster->focus;
	kprintf("insert record slave %d %d.%016jx\n",
		i, focus->bref.type, focus->bref.key);

	focus = cluster->focus;
	chain = NULL;
	hammer2_chain_create(&thr->trans, &cparent->array[i].chain,
			     &chain, thr->pmp,
			     focus->bref.key, focus->bref.keybits,
			     focus->bref.type, focus->bytes,
			     0);
	hammer2_chain_modify(&thr->trans, chain, 0);

	hammer2_chain_lock(focus, HAMMER2_RESOLVE_ALWAYS);

	/* type already set */
	chain->bref.methods = focus->bref.methods;
	/* keybits already set */
	chain->bref.vradix = focus->bref.vradix;
	chain->bref.mirror_tid = focus->bref.mirror_tid;
	chain->bref.modify_tid = focus->bref.modify_tid;
	chain->bref.flags = focus->bref.flags;
	/* key already present */
	/* check code will be recalculated */

	/*
	 * Copy data body.
	 */
	switch(chain->bref.type) {
	case HAMMER2_BREF_TYPE_INODE:
		if ((focus->data->ipdata.op_flags &
		     HAMMER2_OPFLAG_DIRECTDATA) == 0) {
			bcopy(focus->data, chain->data,
			      offsetof(hammer2_inode_data_t, u));
			break;
		}
		/* fall through */
	case HAMMER2_BREF_TYPE_DATA:
		bcopy(focus->data, chain->data, chain->bytes);
		break;
	default:
		KKASSERT(0);
		break;
	}

	hammer2_chain_unlock(focus);

	hammer2_chain_ref(chain);		/* replace lock with ref */
	hammer2_chain_unlock(chain);
	cluster->array[i].chain = chain;	/* validate cluster */
	cluster->array[i].flags &= ~HAMMER2_CITEM_INVALID;

	return 0;
}

/*
 * cparent is locked exclusively, with an extra ref, cluster is not locked.
 */
static
int
hammer2_sync_destroy(hammer2_syncthr_t *thr,
		     hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
		     int i, int *errors)
{
	hammer2_chain_t *chain;

	chain = cluster->array[i].chain;
	kprintf("destroy record slave %d %d.%016jx\n",
		i, chain->bref.type, chain->bref.key);

	hammer2_chain_lock(chain, HAMMER2_RESOLVE_NEVER);
	hammer2_chain_delete(&thr->trans, cparent->array[i].chain, chain, 0);
	hammer2_chain_unlock(chain);

	return 0;
}

/*
 * cparent is locked exclusively, with an extra ref, cluster is not locked.
 */
static
int
hammer2_sync_replace(hammer2_syncthr_t *thr,
		     hammer2_cluster_t *cparent, hammer2_cluster_t *cluster,
		     int i, int *errors)
{
	hammer2_chain_t *focus;
	hammer2_chain_t *chain;
	int nradix;

	focus = cluster->focus;
	chain = cluster->array[i].chain;
	kprintf("replace record slave %d %d.%016jx\n",
		i, focus->bref.type, focus->bref.key);
	if (cluster->focus_index < i)
		hammer2_chain_lock(focus, HAMMER2_RESOLVE_ALWAYS);
	hammer2_chain_lock(chain, HAMMER2_RESOLVE_ALWAYS);
	if (cluster->focus_index >= i)
		hammer2_chain_lock(focus, HAMMER2_RESOLVE_ALWAYS);
	if (chain->bytes != focus->bytes) {
		/* XXX what if compressed? */
		nradix = hammer2_getradix(chain->bytes);
		hammer2_chain_resize(&thr->trans, NULL,
				     cparent->array[i].chain, chain,
				     nradix, 0);
	}
	hammer2_chain_modify(&thr->trans, chain, 0);
	chain->bref.type = focus->bref.type;
	chain->bref.methods = focus->bref.methods;
	chain->bref.keybits = focus->bref.keybits;
	chain->bref.vradix = focus->bref.vradix;
	chain->bref.mirror_tid = focus->bref.mirror_tid;
	chain->bref.modify_tid = focus->bref.modify_tid;
	chain->bref.flags = focus->bref.flags;
	/* key already present */
	/* check code will be recalculated */

	/*
	 * Copy data body.
	 */
	switch(chain->bref.type) {
	case HAMMER2_BREF_TYPE_INODE:
		if ((focus->data->ipdata.op_flags &
		     HAMMER2_OPFLAG_DIRECTDATA) == 0) {
			bcopy(focus->data, chain->data,
			      offsetof(hammer2_inode_data_t, u));
			break;
		}
		/* fall through */
	case HAMMER2_BREF_TYPE_DATA:
		bcopy(focus->data, chain->data, chain->bytes);
		break;
	default:
		KKASSERT(0);
		break;
	}

	hammer2_chain_unlock(focus);
	hammer2_chain_unlock(chain);

	/* validate cluster */
	cluster->array[i].flags &= ~HAMMER2_CITEM_INVALID;

	return 0;
}
