//Coto: dirent.h part1
//Newlib 2.1 for NDS dirent.h (sys/dirent.h)
//These abstract defs are required by newlib 2.1 and TGDS proyects for filesystem routines to work.

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#ifdef __cplusplus
extern "C" {
#endif

#define __dirfd(dp)	((dp)->dd_fd)
#include <sys/types.h>
#include <limits.h>

#define NAME_MAX (int)(0x100)	//256 bytes posix character len as standard
#define OPEN_MAXFILEDES (int)(20)		//Available POSIX File Descriptors	//aka OPEN_MAX
#define MAXNAMLEN	NAME_MAX	//required by newlib parts

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

#ifdef __cplusplus
}
#endif 

#endif
