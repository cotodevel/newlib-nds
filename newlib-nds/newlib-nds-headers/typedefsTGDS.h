
/*

			Copyright (C) 2017  Coto
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
USA

*/


//this toolchain will always use typedefsTGDS.h as source for typedefs across codebase.

#ifndef __typedefs_common_
#define __typedefs_common_

#include <stdint.h>
#include <stdbool.h>

#include <time.h>
#include <sys/time.h>

typedef	unsigned	short	ushort;
typedef	unsigned	char	uchar;

typedef	signed long long	sint64;
typedef	int					sint32;
typedef	short				sint16;
typedef	char				sint8;
typedef	sint8				bool8;

typedef volatile sint64		vsint64;
typedef volatile sint32		vsint32;
typedef volatile sint16		vsint16;
typedef volatile sint8		vsint8;

typedef unsigned 	long long uint64;
typedef unsigned 	long 	uLong;
typedef	unsigned	int		uint32;
typedef	unsigned	short	uint16;
typedef	unsigned	char	uint8;

typedef volatile uint64		vuint64;
typedef volatile uint32		vuint32;
typedef volatile uint16		vuint16;
typedef volatile uint8		vuint8;

//legacy code

typedef vuint64		vu64;
typedef vuint32		vu32;
typedef vuint16		vu16;
typedef vuint8		vu8;

typedef uint64		u64;
typedef uint32		u32;
typedef uint16		u16;
typedef uint8		u8;

typedef sint64		s64;
typedef sint32		s32;
typedef sint16		s16;
typedef sint8		s8;

//posix
typedef vuint64		vuint64_t;
typedef vuint32		vuint32_t;
typedef vuint16		vuint16_t;
typedef vuint8		vuint8_t;

typedef uint64		uint64_t;
//typedef uint32		uint32_t;
typedef uint16		uint16_t;
typedef uint8		uint8_t;

typedef sint64		int64_t;
//typedef sint32		int32_t;
typedef sint16		int16_t;
//typedef sint8		int8_t;



#endif

#ifdef __cplusplus
extern "C"{
#endif

extern int printf(const char *, ...);
extern void _exit(int rc);

extern int read(int fd, void *buf, int count);
extern int write(int fd, const void *buf, int count);
extern void abort();
extern int _isatty(int fd);

#ifdef __cplusplus
}
#endif