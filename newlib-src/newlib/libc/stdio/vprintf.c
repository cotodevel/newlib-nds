/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/* doc in vfprintf.c */

#include <_ansi.h>
#include <reent.h>
#include <stdio.h>
#ifdef _HAVE_STDC
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "local.h"

extern int _vfprintf_r(void *reent, FILE *fp, const char *fmt, va_list list);

#ifndef _REENT_ONLY

int
_DEFUN(vprintf, (fmt, ap),
       _CONST char *fmt _AND
       va_list ap)
{
  struct _reent *reent = _REENT;

  _REENT_SMALL_CHECK_INIT (reent);
  return _vfprintf_r (reent, _stdout_r (reent), fmt, ap);
}

int
_EXFUN(viprintf, (const char *, __VALIST)
       _ATTRIBUTE ((alias("vprintf"))));
#endif /* !_REENT_ONLY */

int
_DEFUN(_vprintf_r, (ptr, fmt, ap),
       struct _reent *ptr _AND
       _CONST char *__restrict fmt   _AND
       va_list ap)
{
  _REENT_SMALL_CHECK_INIT (ptr);
  return _vfprintf_r (ptr, _stdout_r (ptr), fmt, ap);
}

int
_EXFUN(_viprintf_r, (struct _reent *, const char *, __VALIST)
       _ATTRIBUTE ((alias("_vprintf_r"))));
