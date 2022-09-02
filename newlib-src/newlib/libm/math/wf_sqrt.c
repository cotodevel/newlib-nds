#ifdef ARM9

#include "typedefsTGDS.h"

#define SQRT_CR				(*(vuint16*)(0x040002B0))
#define SQRT_PARAM64		(*(vint64*) (0x040002B8))
#define SQRT_RESULT32		(*(vsint32*) (0x040002B4))
#define SQRT_PARAM32		(*(vsint32*) (0x040002B8))

#define SQRT_64				1
#define SQRT_32				0
#define SQRT_BUSY			(1<<15)

#define floattof32(n)        ((int)((n) * (1 << 12)))
#define f32toint(n)          (n >> 12)

#endif


/* wf_sqrt.c -- float version of w_sqrt.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* 
 * wrapper sqrtf(x)
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	float sqrtf(float x)		/* wrapper sqrtf */
#else
	float sqrtf(x)			/* wrapper sqrtf */
	float x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_sqrtf(x);
#else
	float z;
	struct exception exc;
	z = __ieee754_sqrtf(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(x<(float)0.0) {
            /* sqrtf(negative) */
            exc.type = DOMAIN;
            exc.name = "sqrtf";
	    exc.err = 0;
	    exc.arg1 = exc.arg2 = (double)x;
            if (_LIB_VERSION == _SVID_)
              exc.retval = 0.0;
            else
              exc.retval = 0.0/0.0;
            if (_LIB_VERSION == _POSIX_) 
              errno = EDOM;
            else if (!matherr(&exc)) {
              errno = EDOM;
            }
            if (exc.err != 0)
	      errno = exc.err;
	    return (float)exc.retval; 
	} else
	    return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double sqrt(double x)
#else
	double sqrt(x)
	double x;
#endif
{
	#ifdef ARM7
	return (double) sqrtf((float) x);
	#endif
	
	#ifdef ARM9
	SQRT_CR = SQRT_32;
	//while(SQRT_CR & SQRT_BUSY);
	SQRT_PARAM32 = f32toint(floattof32(x));
	while(SQRT_CR & SQRT_BUSY);
	return SQRT_RESULT32;
	#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
