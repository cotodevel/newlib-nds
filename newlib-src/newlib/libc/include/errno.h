#ifndef __ERRNO_H__
#define __ERRNO_H__

#ifndef __error_t_defined
typedef int error_t;
#define __error_t_defined 1
#endif

#include <sys/errno.h>

extern int __set_errno(int n);

#endif /* !__ERRNO_H__ */
