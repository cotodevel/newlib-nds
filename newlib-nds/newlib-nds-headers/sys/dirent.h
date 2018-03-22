#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file was written to be compatible with the BSD directory
 * routines, so it looks like it.  But it was written from scratch.
 * Sean Eric Fagan, sef@Kithrup.COM
 *
 *  Copied to RTEMS configuration without modification.
 */
/*
typedef struct _dirdesc {
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	*dd_buf;
	int	dd_len;
	long	dd_seek;
} DIR;
*/
# define __dirfd(dp)	((dp)->dd_fd)


#include <sys/types.h>

#include <limits.h>
#define NAME_MAX 512

//this dirent is guaranteed to work with fsfat, add items if you want but don't edit those definitions.
struct dirent {
	ino_t d_ino;				/* file serial number */ //used as struct fd index ( fd_struct_get(fd) ), assigned when open newlib posix call, and freed when close newlib posix call
    char d_name[NAME_MAX+1];	/* name must be no longer than this */
};

#ifdef __cplusplus
}
#endif 


#endif
