/*-
 * Copyright (c) 2002 Mitsuru IWASAKI
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/amd64/include/acpica_machdep.h,v 1.6 2004/10/11 05:39:15 njl Exp $
 */

/******************************************************************************
 *
 * Name: acpica_machdep.h - arch-specific defines, etc.
 *       $Revision$
 *
 *****************************************************************************/

#ifndef _MACHINE_ACPICA_MACHDEP_H_
#define	_MACHINE_ACPICA_MACHDEP_H_

#ifdef _KERNEL
#define	ACPI_DISABLE_IRQS()	cpu_disable_intr()
#define	ACPI_ENABLE_IRQS()	cpu_enable_intr()
#define	ACPI_FLUSH_CPU_CACHE()	wbinvd()

/* Section 5.2.9.1:  global lock acquire/release functions */
extern int	acpi_acquire_global_lock(uint32_t *lock);
extern int	acpi_release_global_lock(uint32_t *lock);
#define	ACPI_ACQUIRE_GLOBAL_LOCK(FACSptr, Acq) \
		((Acq) = acpi_acquire_global_lock(&(FACSptr)->GlobalLock))
#define	ACPI_RELEASE_GLOBAL_LOCK(FACSptr, Acq) \
		((Acq) = acpi_release_global_lock(&(FACSptr)->GlobalLock))
#endif /* _KERNEL */

#endif /* _MACHINE_ACPICA_MACHDEP_H_ */
