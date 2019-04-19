#include <errno.h>

int __set_errno(int n)
{
    errno = n;
    return -1;
}