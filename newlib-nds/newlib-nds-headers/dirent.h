//Coto: dirent.h part2
//Newlib 2.1 for NDS dirent.h (dirent.h).
//These abstract defs are required by newlib 2.1 and TGDS proyects for filesystem routines to work.

#ifndef _DIRENT_H
#define _DIRENT_H

#include <sys/dirent.h>

//this dirent is guaranteed to work with fatfs, add items if you want but don't edit those definitions.
struct dirent {
	ino_t d_ino;				/* file serial number */ //used as struct fd index ( fd_struct_get(fd) ), assigned when open newlib posix call, and freed when close newlib posix call
    char d_name[NAME_MAX+1];	/* name must be no longer than this */
};

#endif