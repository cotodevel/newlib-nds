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
/* doc in sprintf.c */

#include <_ansi.h>
#include <reent.h>
#include <stdio.h>
#include <stdarg.h>

extern int _vfprintf_r(struct _reent *reent, FILE *fp, const char *fmt, va_list list);

int _DEFUN(_fprintf_r, (ptr, fp, fmt),
       struct _reent *ptr _AND
       FILE *__restrict fp _AND
       const char *__restrict fmt _DOTS)
{
  int ret;
  va_list ap;

  va_start (ap, fmt);
  ret = _vfprintf_r (ptr, fp, fmt, ap);
  va_end (ap);
  return ret;
}

int
_EXFUN(_fiprintf_r, (struct _reent *, FILE *, const char *, ...)
       _ATTRIBUTE ((alias("_fprintf_r"))));
#ifndef _REENT_ONLY

int
_DEFUN(fprintf, (fp, fmt),
       FILE *__restrict fp _AND
       const char *__restrict fmt _DOTS)
{
  int ret;
  va_list ap;

  va_start (ap, fmt);
  ret = _vfprintf_r (_REENT, fp, fmt, ap);
  va_end (ap);
  return ret;
}

int
_EXFUN(fiprintf, (FILE *, const char *, ...)
       _ATTRIBUTE ((alias("fprintf"))));
#endif /* ! _REENT_ONLY */
