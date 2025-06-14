/* connector for isatty */

#include <reent.h>
#include <unistd.h>

extern int _isatty(int __fildes);

int
_DEFUN (isatty, (fd),
     int fd)
{
#ifdef REENTRANT_SYSCALLS_PROVIDED
  return _isatty_r (_REENT, fd);
#else
  return _isatty (fd);
#endif
}
