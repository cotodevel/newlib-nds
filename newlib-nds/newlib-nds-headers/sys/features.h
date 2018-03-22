/*
 *  Written by Joel Sherrill <joel@OARcorp.com>.
 *
 *  COPYRIGHT (c) 1989-2000.
 *
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Permission to use, copy, modify, and distribute this software for any
 *  purpose without fee is hereby granted, provided that this entire notice
 *  is included in all copies of any software which is or includes a copy
 *  or modification of this software.
 *
 *  THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 *  WARRANTY.  IN PARTICULAR,  THE AUTHOR MAKES NO REPRESENTATION
 *  OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY OF THIS
 *  SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 *  $Id$
 */

#ifndef _SYS_FEATURES_H
#define _SYS_FEATURES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Macro to test version of GCC.  Returns 0 for non-GCC or too old GCC. */
#ifndef __GNUC_PREREQ
# if defined __GNUC__ && defined __GNUC_MINOR__
#  define __GNUC_PREREQ(maj, min) \
	((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
# else
#  define __GNUC_PREREQ(maj, min) 0
# endif
#endif /* __GNUC_PREREQ */
/* Version with trailing underscores for BSD compatibility. */
#define	__GNUC_PREREQ__(ma, mi)	__GNUC_PREREQ(ma, mi)

#if !defined(_POSIX_C_SOURCE)  &&  defined(_XOPEN_SOURCE) 
  #if (_XOPEN_SOURCE - 0) == 700	/* POSIX.1-2008 */
    #define _POSIX_C_SOURCE       200809L
   #elif (_XOPEN_SOURCE - 0) == 600	/* POSIX.1-2001 or 2004 */
    #define _POSIX_C_SOURCE       200112L
   #elif (_XOPEN_SOURCE - 0) == 500	/* POSIX.1-1995 */
    #define _POSIX_C_SOURCE       199506L
   #elif (_XOPEN_SOURCE - 0) < 500	/* really old */
    #define _POSIX_C_SOURCE       2
  #endif
#endif

#ifdef __cplusplus
}
#endif
#endif /* _SYS_FEATURES_H */