/*
 *  $Id$
 */

#ifndef _MACHINE__DEFAULT_TYPES_H
#define _MACHINE__DEFAULT_TYPES_H

#include <sys/features.h>

/*
 * Guess on types by examining *_MIN / *_MAX defines.
 */
#if __GNUC_PREREQ (3, 3)
/* GCC >= 3.3.0 has __<val>__ implicitly defined. */
#define __EXP(x) __##x##__
#else
/* Fall back to POSIX versions from <limits.h> */
#define __EXP(x) x
#include <limits.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif






//types init


/* gids, uids, and pids are all 32-bit. */
typedef __kernel_gid32_t __gid_t;
typedef __gid_t gid_t;
typedef __kernel_uid32_t __uid_t;
typedef __uid_t uid_t;
typedef __kernel_pid_t __pid_t;
typedef __pid_t pid_t;
typedef uint32_t __id_t;
typedef __id_t id_t;
typedef unsigned long blkcnt_t;
typedef unsigned long blksize_t;
typedef __kernel_caddr_t caddr_t;
typedef __kernel_clock_t clock_t;
typedef __kernel_clockid_t __clockid_t;
typedef __clockid_t clockid_t;
typedef __kernel_daddr_t daddr_t;
typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;
typedef __kernel_mode_t __mode_t;
typedef __mode_t mode_t;
typedef __kernel_key_t __key_t;
typedef __key_t key_t;
typedef __kernel_ino_t __ino_t;
typedef __ino_t ino_t;
typedef uint64_t ino64_t;
typedef uint32_t __nlink_t;
typedef __nlink_t nlink_t;
typedef void* __timer_t;
typedef __timer_t timer_t;
typedef __kernel_suseconds_t __suseconds_t;
typedef __suseconds_t suseconds_t;
/* useconds_t is 32-bit on both LP32 and LP64. */
typedef uint32_t __useconds_t;
typedef __useconds_t useconds_t;
#if !defined(__LP64__)
/* This historical accident means that we had a 32-bit dev_t on 32-bit architectures. */
typedef uint32_t dev_t;
#else
typedef uint64_t dev_t;
#endif
/* This historical accident means that we had a 32-bit time_t on 32-bit architectures. */
typedef __kernel_time_t __time_t;
typedef __time_t time_t;
#if defined(__USE_FILE_OFFSET64) || defined(__LP64__)
typedef int64_t off_t;
typedef off_t loff_t;
typedef loff_t off64_t;
#else
/* This historical accident means that we had a 32-bit off_t on 32-bit architectures. */
typedef __kernel_off_t off_t;
typedef __kernel_loff_t loff_t;
typedef loff_t off64_t;
#endif

#if !defined(__LP64__)
/* This historical accident means that we had a signed socklen_t on 32-bit architectures. */
typedef int32_t __socklen_t;
#else
/* LP64 still has a 32-bit socklen_t. */
typedef uint32_t __socklen_t;
#endif
typedef __socklen_t socklen_t;
#ifndef _SSIZE_T_DEFINED_
#define _SSIZE_T_DEFINED_
/* Traditionally, bionic's ssize_t was "long int". This caused GCC to emit warnings when you
 * pass a ssize_t to a printf-style function. The correct type is __kernel_ssize_t, which is
 * "int", which isn't an ABI change for C code (because they're the same size) but is an ABI
 * change for C++ because "int" and "long int" mangle to "i" and "l" respectively. So until
 * we can fix the ABI, this change should not be propagated to the NDK. http://b/8253769. */
typedef __kernel_ssize_t ssize_t;
#endif
typedef unsigned int        uint_t;
typedef unsigned int        uint;
#if defined(__USE_BSD)
#include <sys/sysmacros.h>
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef unsigned long  u_long;
typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;
typedef uint8_t  u_int8_t;
typedef uint64_t u_int64_t;
#endif
#endif


///types end

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ __int8_t;
typedef __UINT8_TYPE__ __uint8_t;
#define ___int8_t_defined 1
#elif __EXP(SCHAR_MAX) == 0x7f
typedef signed char __int8_t ;
typedef unsigned char __uint8_t ;
#define ___int8_t_defined 1
#endif

#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ __int16_t;
typedef __UINT16_TYPE__ __uint16_t;
#define ___int16_t_defined 1
#elif __EXP(INT_MAX) == 0x7fff
typedef signed int __int16_t;
typedef unsigned int __uint16_t;
#define ___int16_t_defined 1
#elif __EXP(SHRT_MAX) == 0x7fff
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
#define ___int16_t_defined 1
#elif __EXP(SCHAR_MAX) == 0x7fff
typedef signed char __int16_t;
typedef unsigned char __uint16_t;
#define ___int16_t_defined 1
#endif

#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ __int32_t;
typedef __UINT32_TYPE__ __uint32_t;
#define ___int32_t_defined 1
#elif __EXP(INT_MAX) == 0x7fffffffL
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
#define ___int32_t_defined 1
#elif __EXP(LONG_MAX) == 0x7fffffffL
typedef signed long __int32_t;
typedef unsigned long __uint32_t;
#define ___int32_t_defined 1
#elif __EXP(SHRT_MAX) == 0x7fffffffL
typedef signed short __int32_t;
typedef unsigned short __uint32_t;
#define ___int32_t_defined 1
#elif __EXP(SCHAR_MAX) == 0x7fffffffL
typedef signed char __int32_t;
typedef unsigned char __uint32_t;
#define ___int32_t_defined 1
#endif

#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ __int64_t;
typedef __UINT64_TYPE__ __uint64_t;
#define ___int64_t_defined 1
#elif __EXP(LONG_MAX) > 0x7fffffff
typedef signed long __int64_t;
typedef unsigned long __uint64_t;
#define ___int64_t_defined 1

/* GCC has __LONG_LONG_MAX__ */
#elif  defined(__LONG_LONG_MAX__) && (__LONG_LONG_MAX__ > 0x7fffffff)
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;
#define ___int64_t_defined 1

/* POSIX mandates LLONG_MAX in <limits.h> */
#elif  defined(LLONG_MAX) && (LLONG_MAX > 0x7fffffff)
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;
#define ___int64_t_defined 1

#elif  __EXP(INT_MAX) > 0x7fffffff
typedef signed int __int64_t;
typedef unsigned int __uint64_t;
#define ___int64_t_defined 1
#endif

#ifdef __INT_LEAST8_TYPE__
typedef __INT_LEAST8_TYPE__ __int_least8_t;
typedef __UINT_LEAST8_TYPE__ __uint_least8_t;
#define ___int_least8_t_defined 1
#elif defined(___int8_t_defined)
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
#define ___int_least8_t_defined 1
#elif defined(___int16_t_defined)
typedef __int16_t __int_least8_t;
typedef __uint16_t __uint_least8_t;
#define ___int_least8_t_defined 1
#elif defined(___int32_t_defined)
typedef __int32_t __int_least8_t;
typedef __uint32_t __uint_least8_t;
#define ___int_least8_t_defined 1
#elif defined(___int64_t_defined)
typedef __int64_t __int_least8_t;
typedef __uint64_t __uint_least8_t;
#define ___int_least8_t_defined 1
#endif

#ifdef __INT_LEAST16_TYPE__
typedef __INT_LEAST16_TYPE__ __int_least16_t;
typedef __UINT_LEAST16_TYPE__ __uint_least16_t;
#define ___int_least16_t_defined 1
#elif defined(___int16_t_defined)
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
#define ___int_least16_t_defined 1
#elif defined(___int32_t_defined)
typedef __int32_t __int_least16_t;
typedef __uint32_t __uint_least16_t;
#define ___int_least16_t_defined 1
#elif defined(___int64_t_defined)
typedef __int64_t __int_least16_t;
typedef __uint64_t __uint_least16_t;
#define ___int_least16_t_defined 1
#endif

#ifdef __INT_LEAST32_TYPE__
typedef __INT_LEAST32_TYPE__ __int_least32_t;
typedef __UINT_LEAST32_TYPE__ __uint_least32_t;
#define ___int_least32_t_defined 1
#elif defined(___int32_t_defined)
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
#define ___int_least32_t_defined 1
#elif defined(___int64_t_defined)
typedef __int64_t __int_least32_t;
typedef __uint64_t __uint_least32_t;
#define ___int_least32_t_defined 1
#endif

#ifdef __INT_LEAST64_TYPE__
typedef __INT_LEAST64_TYPE__ __int_least64_t;
typedef __UINT_LEAST64_TYPE__ __uint_least64_t;
#define ___int_least64_t_defined 1
#elif defined(___int64_t_defined)
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;
#define ___int_least64_t_defined 1
#endif

#ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ __intptr_t;
typedef __UINTPTR_TYPE__ __uintptr_t;
#elif defined(__PTRDIFF_TYPE__)
typedef __PTRDIFF_TYPE__ __intptr_t;
typedef unsigned __PTRDIFF_TYPE__ __uintptr_t;
#else
typedef long __intptr_t;
typedef unsigned long __uintptr_t;
#endif


#undef __EXP

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE__DEFAULT_TYPES_H */
