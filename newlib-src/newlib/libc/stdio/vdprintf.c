/* Copyright 2005, 2007 Shaun Jackman
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */
/* doc in dprintf.c */

#include <_ansi.h>
#include <reent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <malloc.h>
#include "local.h"

int
_DEFUN(_vdprintf_r, (ptr, fd, format, ap),
       struct _reent *ptr _AND
       int fd _AND
       const char *__restrict format _AND
       va_list ap)
{
  char *p;
  char buf[512];
  size_t n = sizeof buf;

  _REENT_SMALL_CHECK_INIT (ptr);
  p = _vasnprintf_r (ptr, buf, &n, format, ap);
  if (!p)
    return -1;
  n = _write_r (ptr, fd, p, n);
  if (p != buf)
    _free_r (ptr, p);
  return n;
}

int
_EXFUN(_vdiprintf_r, (struct _reent *, int, const char *, __VALIST)
       _ATTRIBUTE ((alias("_vdprintf_r"))));
#ifndef _REENT_ONLY

int
_DEFUN(vdprintf, (fd, format, ap),
       int fd _AND
       const char *__restrict format _AND
       va_list ap)
{
  return _vdprintf_r (_REENT, fd, format, ap);
}

int
_EXFUN(vdiprintf, (int, const char *, __VALIST)
       _ATTRIBUTE ((alias("vdprintf"))));
#endif /* ! _REENT_ONLY */
