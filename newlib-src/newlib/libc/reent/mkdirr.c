/* Reentrant versions of mkdir system call. */

#include <reent.h>
#include <unistd.h>
#include <_syslist.h>

extern int _mkdir _PARAMS ((const char *, int));
/* Some targets provides their own versions of this functions.  Those
   targets should define REENTRANT_SYSCALLS_PROVIDED in TARGET_CFLAGS.  */

#ifdef _REENT_ONLY
#ifndef REENTRANT_SYSCALLS_PROVIDED
#define REENTRANT_SYSCALLS_PROVIDED
#endif
#endif

#ifndef REENTRANT_SYSCALLS_PROVIDED

/* We use the errno variable used by the system dependent layer.  */
#undef errno
extern int errno;

/*
FUNCTION
	<<_mkdir_r>>---Reentrant version of mkdir
	
INDEX
	_mkdir_r

ANSI_SYNOPSIS
	#include <reent.h>
	int _mkdir_r(struct _reent *<[ptr]>,
		     const char *<[path]>, int <[mode]>);

TRAD_SYNOPSIS
	#include <reent.h>
	int _mkdir_r(<[ptr]>, <[path]>, <[mode]>)
	struct _reent *<[ptr]>;
	char *<[path]>;
	int <[mode]>;

DESCRIPTION
	This is a reentrant version of <<mkdir>>.  It
	takes a pointer to the global data block, which holds
	<<errno>>.
*/

#include <sys/stat.h>

int
_DEFUN (_mkdir_r, (ptr, path, mode),
     struct _reent *ptr _AND
     _CONST char *path _AND
     int mode)
{
  int ret;

  errno = 0;
  if ((ret = _mkdir (path, mode)) == -1 && errno != 0)
    ptr->_errno = errno;
  return ret;
}


#endif /* ! defined (REENTRANT_SYSCALLS_PROVIDED) */
