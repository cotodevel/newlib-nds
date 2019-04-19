//Coto: dirent.h part1
//Newlib 2.1 for NDS dirent.h (sys/dirent.h)
//These abstract defs are required by newlib 2.1 and TGDS proyects for filesystem routines to work.

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H


#include <sys/types.h>
#include <limits.h>

#define __dirfd(dp)	((dp)->dd_fd)

#define NAME_MAX 256	//256 bytes posix character len as standard : /* max bytes in a file name */
#define OPEN_MAXFILEDES 20		//Available POSIX File Descriptors	//aka OPEN_MAX
#define MAXNAMLEN	NAME_MAX	//required by newlib parts
#define FILENAME_MAX	MAXNAMLEN	//required by newlib parts
#define PATH_MAX	FILENAME_MAX

/*
 * File types
 */
#define	DT_UNKNOWN	 0
#define	DT_FIFO		 1
#define	DT_CHR		 2
#define	DT_DIR		 4
#define	DT_BLK		 6
#define	DT_REG		 8
#define	DT_LNK		10
#define	DT_SOCK		12

/*
 * Convert between stat structure types and directory types.
 */
#define	IFTODT(mode)	(((mode) & 0170000) >> 12)
#define	DTTOIF(dirtype)	((dirtype) << 12)

#endif
