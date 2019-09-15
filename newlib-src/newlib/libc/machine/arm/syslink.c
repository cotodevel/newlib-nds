#include "typedefsTGDS.h"
#include <errno.h>

/* The system does not support symlinks.  */
int symlink (char const *contents ,
         char const *name)
{
	errno = ENOSYS;
	return -1;
}