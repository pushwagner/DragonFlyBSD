#  $OpenBSD: Makefile,v 1.118 2018/03/10 20:52:58 kettenis Exp $
#  $NetBSD: Makefile,v 1.28 1995/11/20 22:06:19 jtc Exp $
#
#  @(#)Makefile 5.1beta 93/09/24
#
#  ====================================================
#  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
#
#  Developed at SunPro, a Sun Microsystems, Inc. business.
#  Permission to use, copy, modify, and distribute this
#  software is freely granted, provided that this notice
#  is preserved.
#  ====================================================

OPENSRC=	${.CURDIR}/../../contrib/openbsd_libm
LIBCDIR=	${.CURDIR}/../libc
SYM_MAPS=	${.CURDIR}/Symbol.map
VERSION_DEF=	${LIBCDIR}/Versions.def
SYMBOL_MAPS=	${SYM_MAPS}
LIB=		m
SHLIB_MAJOR=	4
SHLIBDIR?=	/lib
WARNS?=		3 # unused-but-set (almost 4)

INCSGROUPS=	INCS MACHINCS
INCS=		global/complex.h global/fenv.h global/math.h global/tgmath.h
MACHINCSDIR=	${INCLUDEDIR}/machine

.PATH:	${OPENSRC}/include
.PATH:	${OPENSRC}/man
.PATH:	${.CURDIR}/man
.PATH:	${OPENSRC}/src
.PATH:	${.CURDIR}/src

.if (${MACHINE_ARCH} == "x86_64")
.PATH:	${OPENSRC}/arch/amd64
MACHINCS=   amd64/fenv.h amd64/ieee.h
CPPFLAGS+=  -I${OPENSRC}/arch/amd64
SYM_MAPS+=  ${.CURDIR}/Symbol.map.x86_64
ARCH_SRCS = e_acos.S e_asin.S e_atan2.S e_exp.S e_fmod.S e_log.S e_log10.S \
	    e_remainder.S e_remainderf.S e_scalb.S e_sqrt.S e_sqrtf.S \
	    e_sqrtl.S \
	    invtrig.c \
	    s_atan.S s_atanf.S s_ceil.S s_ceilf.S s_copysign.S s_copysignf.S \
	    s_cos.S s_cosf.S s_floor.S s_floorf.S \
	    s_ilogb.S s_ilogbf.S s_log1p.S s_log1pf.S s_logb.S s_logbf.S \
	    s_llrint.S s_llrintf.S s_lrint.S s_lrintf.S \
	    s_rint.S s_rintf.S s_scalbnf.S s_significand.S \
	    s_significandf.S s_sin.S s_sinf.S s_tan.S s_tanf.S
.endif

COMMON_SRCS = b_exp__D.c b_log__D.c b_tgamma.c \
	e_acos.c e_acosf.c e_acosh.c e_acoshf.c e_asin.c e_asinf.c \
	e_atan2.c e_atan2f.c e_atanh.c e_atanhf.c e_cosh.c e_coshf.c e_exp.c \
	e_expf.c e_fmod.c e_fmodf.c e_hypot.c e_hypotf.c e_j0.c e_j0f.c \
	e_j1.c e_j1f.c e_jn.c e_jnf.c e_lgamma_r.c e_lgammaf_r.c e_log.c \
	e_log10.c e_log10f.c e_log2.c e_log2f.c e_logf.c e_pow.c e_powf.c \
	e_rem_pio2.c \
	e_rem_pio2f.c e_remainder.c e_remainderf.c e_scalb.c e_scalbf.c \
	e_sinh.c e_sinhf.c e_sqrt.c e_sqrtf.c \
	fenv.c \
	k_cos.c k_cosf.c k_rem_pio2.c k_rem_pio2f.c k_sin.c k_sinf.c \
	k_tan.c k_tanf.c \
	s_lround.c s_lroundf.c s_llround.c s_llroundf.c \
	s_asinh.c s_asinhf.c s_atan.c s_atanf.c s_cabsf.c \
	s_cacosf.c s_cacoshf.c s_cargf.c \
	s_casinf.c s_casinhf.c s_catanf.c \
	s_catanhf.c s_cbrt.c s_cbrtf.c s_ccosf.c \
	s_ccoshf.c s_ceil.c \
	s_ceilf.c s_cexpf.c s_clogf.c \
	s_copysign.c s_copysignf.c s_cos.c s_cosf.c s_cpowf.c \
	s_csinf.c \
	s_csinhf.c s_csqrtf.c s_ctanf.c \
	s_ctanhf.c s_erf.c s_erff.c s_exp2.c s_exp2f.c s_expm1.c s_expm1f.c \
	s_fabsf.c s_fma.c s_fmaf.c \
	s_floor.c s_floorf.c s_frexpf.c s_ilogb.c s_ilogbf.c \
	s_log1p.c \
	s_log1pf.c s_logb.c s_logbf.c s_llrint.c s_llrintf.c s_lrint.c \
	s_lrintf.c s_modff.c s_nan.c s_nearbyint.c s_nextafter.c \
	s_nextafterf.c s_nexttowardf.c s_remquo.c s_remquof.c s_rint.c \
	s_rintf.c \
	s_scalbn.c s_scalbnf.c s_signgam.c s_significand.c \
	s_significandf.c s_sin.c s_sinf.c s_sincos.c s_sincosf.c \
	s_tan.c s_tanf.c s_tanh.c s_tanhf.c s_trunc.c \
	s_truncf.c w_drem.c w_dremf.c w_gamma.c w_gamma_r.c w_gammaf.c \
	w_gammaf_r.c w_lgamma.c w_lgammaf.c

LONG_SRCS = e_acoshl.c e_acosl.c e_asinl.c e_atan2l.c e_atanhl.c \
	e_coshl.c s_cabsl.c s_cacoshl.c s_cacosl.c s_cargl.c \
	s_casinhl.c s_casinl.c s_catanhl.c s_catanl.c s_ccoshl.c \
	s_ccosl.c s_cexpl.c s_cimagl.c s_clogl.c s_conjl.c s_cpowl.c \
	s_cprojl.c s_creall.c s_csinhl.c s_csinl.c s_csqrtl.c \
	s_ctanhl.c s_ctanl.c e_expl.c e_fmodl.c e_hypotl.c e_lgammal.c \
	e_log10l.c e_log2l.c e_logl.c e_powl.c e_remainderl.c \
	e_sinhl.c e_sqrtl.c e_tgammal.c invtrig.c k_cosl.c k_sinl.c \
	k_tanl.c polevll.c s_asinhl.c s_atanl.c s_cbrtl.c s_ceill.c \
	s_copysignl.c s_cosl.c s_erfl.c s_exp2l.c s_expm1l.c s_fabsl.c \
	s_floorl.c s_fmal.c s_fmaxl.c s_fminl.c s_frexpl.c s_ilogbl.c \
	s_llrintl.c s_llroundl.c s_log1pl.c s_logbl.c s_lrintl.c \
	s_lroundl.c s_modfl.c s_nanl.c s_nextafterl.c s_nexttoward.c \
	s_remquol.c s_rintl.c s_roundl.c s_scalbnl.c s_sinl.c s_sincosl.c \
	s_tanhl.c s_tanl.c s_truncl.c

# math routines that are completely MI
PURE_SRCS = s_cabs.c s_cacos.c s_cacosh.c s_carg.c s_casin.c \
	s_casinh.c s_catan.c s_catanh.c s_ccos.c s_ccosh.c s_cexp.c \
	s_cimag.c s_cimagf.c s_clog.c s_conj.c s_conjf.c s_cpow.c \
	s_creal.c s_crealf.c s_csin.c s_csinh.c s_csqrt.c s_ctan.c \
	s_ctanh.c s_fdim.c s_fmax.c s_fmaxf.c s_fmin.c s_fminf.c \
	s_cproj.c s_cprojf.c s_round.c s_roundf.c s_scalbln.c

# libm is symbol versions so we need to keep previous versions
PAST_SRCS = imprecise.c frexp.c isfinite.c isnanf.c isnormal.c signbit.c

SRCS=	${COMMON_SRCS} ${PURE_SRCS}
SRCS+=	${PAST_SRCS}

# for now do not let the use of -flto
.if ${CFLAGS:M-flto}
CFLAGS+=	-fno-lto
LDFLAGS+=	-flto
.endif

.if (${MACHINE_ARCH} == "x86_64")
.PATH:		${OPENSRC}/src/ld80
.PATH:		${.CURDIR}/src/amd64
CFLAGS+=	-I${OPENSRC}/src -I${OPENSRC}/src/ld80
SRCS+=		${LONG_SRCS}
PAST_SRCS+=	isfinitel.c isnanl.c isnormall.c signbitl.c
.endif

# Substitute common sources with any arch specific sources
.for i in ${ARCH_SRCS}
    SRCS:=${SRCS:S/${i:S/.S/.c/}/$i/}
.endfor

MAN=	acos.3 acosh.3 asin.3 asinh.3 atan.3 atan2.3 atanh.3 ceil.3 \
	copysign.3 cos.3 cosh.3 erf.3 exp.3 \
	fabs.3 \
	fdim.3 feclearexcept.3 feenableexcept.3 fegetenv.3 \
	fegetround.3 floor.3 fma.3 fmax.3 fmod.3 hypot.3 ilogb.3 j0.3 \
	lgamma.3 logb.3 lrint.3 lround.3 nan.3 nextafter.3 \
	remainder.3 rint.3 round.3 scalbn.3 sin.3 sincos.3 sinh.3 sqrt.3 \
	tan.3 tanh.3 trunc.3

MAN+=	cacos.3 cacosh.3 carg.3 casin.3 casinh.3 catan.3 catanh.3 \
	ccos.3 ccosh.3 cexp.3 cimag.3 clog.3 conj.3 cpow.3 cproj.3 \
	creal.3 csin.3 csinh.3 csqrt.3 ctan.3 ctanh.3

MLINKS+=acos.3 acosf.3 \
	acos.3 acosl.3
MLINKS+=acosh.3 acoshf.3 \
	acosh.3 acoshl.3
MLINKS+=asin.3 asinf.3 \
	asin.3 asinl.3
MLINKS+=asinh.3 asinhf.3 \
	asinh.3 asinhl.3
MLINKS+=atan.3 atanf.3 \
	atan.3 atanl.3
MLINKS+=atan2.3 atan2f.3 \
	atan2.3 atan2l.3
MLINKS+=atanh.3 atanhf.3 \
	atanh.3 atanhl.3
MLINKS+=cacos.3 cacosf.3 \
	cacos.3 cacosl.3
MLINKS+=cacosh.3 cacoshf.3 \
	cacosh.3 cacoshl.3
MLINKS+=carg.3 cargf.3 \
	carg.3 cargl.3
MLINKS+=casin.3 casinf.3 \
	casin.3 casinl.3
MLINKS+=casinh.3 casinhf.3 \
	casinh.3 casinhl.3
MLINKS+=catan.3 catanf.3 \
	catan.3 catanl.3
MLINKS+=catanh.3 catanhf.3 \
	catanh.3 catanhl.3
MLINKS+=ccos.3 ccosf.3 \
	ccos.3 ccosl.3
MLINKS+=ccosh.3 ccoshf.3 \
	ccosh.3 ccoshl.3
MLINKS+=ceil.3 ceilf.3 \
	ceil.3 ceill.3
MLINKS+=cexp.3 cexpf.3 \
	cexp.3 cexpl.3
MLINKS+=cimag.3 cimagf.3 \
	cimag.3 cimagl.3
MLINKS+=clog.3 clogf.3 \
	clog.3 clogl.3
MLINKS+=conj.3 conjf.3 \
	conj.3 conjl.3
MLINKS+=copysign.3 copysignf.3 \
	copysign.3 copysignl.3
MLINKS+=cos.3 cosf.3 \
	cos.3 cosl.3
MLINKS+=cosh.3 coshf.3 \
	cosh.3 coshl.3
MLINKS+=cpow.3 cpowf.3 \
	cpow.3 cpowl.3
MLINKS+=cproj.3 cprojf.3 \
	cproj.3 cprojl.3
MLINKS+=creal.3 crealf.3 \
	creal.3 creall.3
MLINKS+=csin.3 csinf.3 \
	csin.3 csinl.3
MLINKS+=csinh.3 csinhf.3 \
	csinh.3 csinhl.3
MLINKS+=csqrt.3 csqrtf.3 \
	csqrt.3 csqrtl.3
MLINKS+=ctan.3 ctanf.3 \
	ctan.3 ctanl.3
MLINKS+=ctanh.3 ctanhf.3 \
	ctanh.3 ctanhl.3
MLINKS+=erf.3 erfc.3 \
	erf.3 erff.3 \
	erf.3 erfcf.3 \
	erf.3 erfl.3 \
	erf.3 erfcl.3
MLINKS+=exp.3 exp2.3 \
	exp.3 exp2f.3 \
	exp.3 exp2l.3 \
	exp.3 expf.3 \
	exp.3 expl.3 \
	exp.3 expm1.3 \
	exp.3 expm1f.3 \
	exp.3 expm1l.3 \
	exp.3 log.3 \
	exp.3 logf.3 \
	exp.3 logl.3 \
	exp.3 log10.3 \
	exp.3 log10f.3 \
	exp.3 log10l.3 \
	exp.3 log1p.3 \
	exp.3 log1pf.3 \
	exp.3 log1pl.3 \
	exp.3 log2.3 \
	exp.3 log2f.3 \
	exp.3 log2l.3 \
	exp.3 pow.3 \
	exp.3 powf.3 \
	exp.3 powl.3
MLINKS+=fabs.3 fabsf.3 \
	fabs.3 fabsl.3
MLINKS+=fdim.3 fdimf.3 \
	fdim.3 fdiml.3
MLINKS+=feclearexcept.3 fegetexceptflag.3 \
	feclearexcept.3 feraiseexcept.3 \
	feclearexcept.3 fesetexceptflag.3 \
	feclearexcept.3 fetestexcept.3
MLINKS+=feenableexcept.3 fedisableexcept.3 \
	feenableexcept.3 fegetexcept.3
MLINKS+=fegetenv.3 feholdexcept.3 \
	fegetenv.3 fesetenv.3 \
	fegetenv.3 feupdateenv.3
MLINKS+=fegetround.3 fesetround.3
MLINKS+=floor.3 floorf.3 \
	floor.3 floorl.3
MLINKS+=fma.3 fmaf.3 \
	fma.3 fmal.3
MLINKS+=fmax.3 fmaxf.3 \
	fmax.3 fmaxl.3 \
	fmax.3 fmin.3 \
	fmax.3 fminf.3 \
	fmax.3 fminl.3
MLINKS+=fmod.3 fmodf.3 \
	fmod.3 fmodl.3
MLINKS+=hypot.3 cabs.3 \
	hypot.3 cabsf.3 \
	hypot.3 cabsl.3 \
	hypot.3 hypotf.3 \
	hypot.3 hypotl.3
MLINKS+=ilogb.3 ilogbf.3 \
	ilogb.3 ilogbl.3
MLINKS+=j0.3 j0f.3 \
	j0.3 j1.3 \
	j0.3 j1f.3 \
	j0.3 jn.3 \
	j0.3 jnf.3 \
	j0.3 y0.3 \
	j0.3 y0f.3 \
	j0.3 y1.3 \
	j0.3 y1f.3 \
	j0.3 yn.3 \
	j0.3 ynf.3
MLINKS+=lgamma.3 lgammaf.3 \
	lgamma.3 lgammal.3 \
	lgamma.3 lgamma_r.3 \
	lgamma.3 lgammaf_r.3 \
	lgamma.3 tgamma.3 \
	lgamma.3 tgammaf.3 \
	lgamma.3 tgammal.3 \
	lgamma.3 gamma.3 \
	lgamma.3 gammaf.3
MLINKS+=logb.3 logbf.3 \
	logb.3 logbl.3 \
	logb.3 scalb.3 \
	logb.3 scalbf.3 \
	logb.3 significand.3 \
	logb.3 significandf.3
MLINKS+=lrint.3 llrint.3 \
	lrint.3 llrintf.3 \
	lrint.3 llrintl.3 \
	lrint.3 lrintf.3 \
	lrint.3 lrintl.3
MLINKS+=lround.3 llround.3 \
	lround.3 llroundf.3 \
	lround.3 llroundl.3 \
	lround.3 lroundf.3 \
	lround.3 lroundl.3
MLINKS+=nan.3 nanf.3 \
	nan.3 nanl.3
MLINKS+=nextafter.3 nextafterf.3 \
	nextafter.3 nextafterl.3 \
	nextafter.3 nexttoward.3 \
	nextafter.3 nexttowardf.3 \
	nextafter.3 nexttowardl.3
MLINKS+=remainder.3 remainderf.3 \
	remainder.3 remainderl.3 \
	remainder.3 remquo.3 \
	remainder.3 remquof.3 \
	remainder.3 remquol.3 \
	remainder.3 drem.3 \
	remainder.3 dremf.3
MLINKS+=rint.3 rintf.3 \
	rint.3 rintl.3 \
	rint.3 nearbyint.3 \
	rint.3 nearbyintf.3 \
	rint.3 nearbyintl.3
MLINKS+=round.3 roundf.3 \
	round.3 roundl.3
MLINKS+=scalbn.3 scalbln.3 \
	scalbn.3 scalblnf.3 \
	scalbn.3 scalblnl.3 \
	scalbn.3 scalbnf.3 \
	scalbn.3 scalbnl.3
MLINKS+=sin.3 sinf.3 \
	sin.3 sinl.3
MLINKS+=sincos.3 sincosf.3 \
	sincos.3 sincosl.3
MLINKS+=sinh.3 sinhf.3 \
	sinh.3 sinhl.3
MLINKS+=sqrt.3 cbrt.3 \
	sqrt.3 cbrtf.3 \
	sqrt.3 cbrtl.3 \
	sqrt.3 sqrtf.3 \
	sqrt.3 sqrtl.3
MLINKS+=tan.3 tanf.3 \
	tan.3 tanl.3
MLINKS+=tanh.3 tanhf.3 \
	tanh.3 tanhl.3
MLINKS+=trunc.3 truncf.3 \
	trunc.3 truncl.3

# additional manual pages that are not part of OpenBSD's libm
#
MAN+=	fpclassify.3 signbit.3

MLINKS+=fpclassify.3 finite.3 \
	fpclassify.3 finitef.3 \
	fpclassify.3 isfinite.3 \
	fpclassify.3 isinf.3 \
	fpclassify.3 isnan.3 \
	fpclassify.3 isnormal.3

.include <bsd.lib.mk>
