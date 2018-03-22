#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/syscall.h"
#include <errno.h>

int
chown (const char *path, short owner, short group)
{
  errno = ENOSYS;
  return -1;
}