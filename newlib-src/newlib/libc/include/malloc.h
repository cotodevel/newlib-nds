/* malloc.h -- header file for memory routines.  */

#ifndef _INCLUDE_MALLOC_H__
#define _INCLUDE_MALLOC_H__

#include <_ansi.h>
#include <sys/reent.h>

#define __need_size_t
#include <stddef.h>

//DS dmalloc
#define FOOTERS 1
#define HAVE_MMAP 0
#define ONLY_MSPACES 0	/* dlmalloc is the default newlib malloc */
#undef MSPACES
#define malloc_getpagesize 4096
#define DEBUG 1
#define ABORT_ON_ASSERT_FAILURE 1
#define ABORT ds_malloc_abort()


#ifndef WIN32
#ifdef _WIN32
#define WIN32 1
#endif  /* _WIN32 */
#endif  /* WIN32 */
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define HAVE_MMAP 1
#define HAVE_MORECORE 0
#define LACKS_UNISTD_H
#define LACKS_SYS_PARAM_H
#define LACKS_SYS_MMAN_H
#define LACKS_STRING_H
#define LACKS_STRINGS_H
#define LACKS_SYS_TYPES_H
#define LACKS_ERRNO_H
#define MALLOC_FAILURE_ACTION
#define MMAP_CLEARS 0 /* WINCE and some others apparently don't clear */
#endif  /* WIN32 */

#if defined(DARWIN) || defined(_DARWIN)
/* Mac OSX docs advise not to use sbrk; it seems better to use mmap */
#ifndef HAVE_MORECORE
#define HAVE_MORECORE 0
#define HAVE_MMAP 1
#endif  /* HAVE_MORECORE */
#endif  /* DARWIN */

#ifndef LACKS_SYS_TYPES_H
#include <sys/types.h>  /* For size_t */
#endif  /* LACKS_SYS_TYPES_H */

/* The maximum possible size_t value has all bits set */
#define MAX_SIZE_T           (~(size_t)0)

#ifndef ONLY_MSPACES
#define ONLY_MSPACES 0
#endif  /* ONLY_MSPACES */
#ifndef MSPACES
#if ONLY_MSPACES
#define MSPACES 1
#else   /* ONLY_MSPACES */
#define MSPACES 0
#endif  /* ONLY_MSPACES */
#endif  /* MSPACES */
#ifndef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT ((size_t)8U)
#endif  /* MALLOC_ALIGNMENT */
#ifndef FOOTERS
#define FOOTERS 0
#endif  /* FOOTERS */
#ifndef ABORT
#define ABORT  abort()
#endif  /* ABORT */
#ifndef ABORT_ON_ASSERT_FAILURE
#define ABORT_ON_ASSERT_FAILURE 1
#endif  /* ABORT_ON_ASSERT_FAILURE */
#ifndef PROCEED_ON_ERROR
#define PROCEED_ON_ERROR 0
#endif  /* PROCEED_ON_ERROR */
#ifndef USE_LOCKS
#define USE_LOCKS 0
#endif  /* USE_LOCKS */
#ifndef INSECURE
#define INSECURE 0
#endif  /* INSECURE */
#ifndef HAVE_MMAP
#define HAVE_MMAP 1
#endif  /* HAVE_MMAP */
#ifndef MMAP_CLEARS
#define MMAP_CLEARS 1
#endif  /* MMAP_CLEARS */
#ifndef HAVE_MREMAP
#ifdef linux
#define HAVE_MREMAP 1
#else   /* linux */
#define HAVE_MREMAP 0
#endif  /* linux */
#endif  /* HAVE_MREMAP */
#ifndef MALLOC_FAILURE_ACTION
#define MALLOC_FAILURE_ACTION  errno = ENOMEM;
#endif  /* MALLOC_FAILURE_ACTION */
#ifndef HAVE_MORECORE
#if ONLY_MSPACES
#define HAVE_MORECORE 0
#else   /* ONLY_MSPACES */
#define HAVE_MORECORE 1
#endif  /* ONLY_MSPACES */
#endif  /* HAVE_MORECORE */
#if !HAVE_MORECORE
#define MORECORE_CONTIGUOUS 0
#else   /* !HAVE_MORECORE */
#ifndef MORECORE
#define MORECORE sbrk
#endif  /* MORECORE */
#ifndef MORECORE_CONTIGUOUS
#define MORECORE_CONTIGUOUS 1
#endif  /* MORECORE_CONTIGUOUS */
#endif  /* HAVE_MORECORE */
#ifndef DEFAULT_GRANULARITY
#if MORECORE_CONTIGUOUS
#define DEFAULT_GRANULARITY (0)  /* 0 means to compute in init_mparams */
#else   /* MORECORE_CONTIGUOUS */
#define DEFAULT_GRANULARITY ((size_t)64U * (size_t)1024U)
#endif  /* MORECORE_CONTIGUOUS */
#endif  /* DEFAULT_GRANULARITY */
#ifndef DEFAULT_TRIM_THRESHOLD
#ifndef MORECORE_CANNOT_TRIM
#define DEFAULT_TRIM_THRESHOLD ((size_t)2U * (size_t)1024U * (size_t)1024U)
#else   /* MORECORE_CANNOT_TRIM */
#define DEFAULT_TRIM_THRESHOLD MAX_SIZE_T
#endif  /* MORECORE_CANNOT_TRIM */
#endif  /* DEFAULT_TRIM_THRESHOLD */
#ifndef DEFAULT_MMAP_THRESHOLD
#if HAVE_MMAP
#define DEFAULT_MMAP_THRESHOLD ((size_t)256U * (size_t)1024U)
#else   /* HAVE_MMAP */
#define DEFAULT_MMAP_THRESHOLD MAX_SIZE_T
#endif  /* HAVE_MMAP */
#endif  /* DEFAULT_MMAP_THRESHOLD */
#ifndef USE_BUILTIN_FFS
#define USE_BUILTIN_FFS 0
#endif  /* USE_BUILTIN_FFS */
#ifndef USE_DEV_RANDOM
#define USE_DEV_RANDOM 0
#endif  /* USE_DEV_RANDOM */
#ifndef NO_MALLINFO
#define NO_MALLINFO 0
#endif  /* NO_MALLINFO */
#ifndef MALLINFO_FIELD_TYPE
#define MALLINFO_FIELD_TYPE size_t
#endif  /* MALLINFO_FIELD_TYPE */


/*
  mallopt tuning options.  SVID/XPG defines four standard parameter
  numbers for mallopt, normally defined in malloc.h.  None of these
  are used in this malloc, so setting them has no effect. But this
  malloc does support the following options.
*/

#define M_TRIM_THRESHOLD     (-1)
#define M_GRANULARITY        (-2)
#define M_MMAP_THRESHOLD     (-3)


#ifdef __cplusplus
extern "C" {
#endif

extern void ds_malloc_abort(void);

/* This version of struct mallinfo must match the one in
   libc/stdlib/mallocr.c.  */
struct mallinfo {
  MALLINFO_FIELD_TYPE arena;    /* non-mmapped space allocated from system */
  MALLINFO_FIELD_TYPE ordblks;  /* number of free chunks */
  MALLINFO_FIELD_TYPE smblks;   /* always 0 */
  MALLINFO_FIELD_TYPE hblks;    /* always 0 */
  MALLINFO_FIELD_TYPE hblkhd;   /* space in mmapped regions */
  MALLINFO_FIELD_TYPE usmblks;  /* maximum total allocated space */
  MALLINFO_FIELD_TYPE fsmblks;  /* always 0 */
  MALLINFO_FIELD_TYPE uordblks; /* total allocated space */
  MALLINFO_FIELD_TYPE fordblks; /* total free space */
  MALLINFO_FIELD_TYPE keepcost; /* releasable (via malloc_trim) space */
};


/* The routines.  */

extern _PTR malloc _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _malloc_r
#define _malloc_r(r, s) malloc (s)
#else
extern _PTR _malloc_r _PARAMS ((struct _reent *, size_t));
#endif

extern _VOID free _PARAMS ((_PTR));
#ifdef __CYGWIN__
#undef _free_r
#define _free_r(r, p) free (p)
#else
extern _VOID _free_r _PARAMS ((struct _reent *, _PTR));
#endif

extern _PTR realloc _PARAMS ((_PTR, size_t));
#ifdef __CYGWIN__
#undef _realloc_r
#define _realloc_r(r, p, s) realloc (p, s)
#else
extern _PTR _realloc_r _PARAMS ((struct _reent *, _PTR, size_t));
#endif

extern _PTR calloc _PARAMS ((size_t, size_t));
#ifdef __CYGWIN__
#undef _calloc_r
#define _calloc_r(r, s1, s2) calloc (s1, s2);
#else
extern _PTR _calloc_r _PARAMS ((struct _reent *, size_t, size_t));
#endif

extern _PTR memalign _PARAMS ((size_t, size_t));
#ifdef __CYGWIN__
#undef _memalign_r
#define _memalign_r(r, s1, s2) memalign (s1, s2);
#else
extern _PTR _memalign_r _PARAMS ((struct _reent *, size_t, size_t));
#endif

extern struct mallinfo mallinfo _PARAMS ((void));
#ifdef __CYGWIN__
#undef _mallinfo_r
#define _mallinfo_r(r) mallinfo ()
#else
extern struct mallinfo _mallinfo_r _PARAMS ((struct _reent *));
#endif

extern void malloc_stats _PARAMS ((void));
#ifdef __CYGWIN__
#undef _malloc_stats_r
#define _malloc_stats_r(r) malloc_stats ()
#else
extern void _malloc_stats_r _PARAMS ((struct _reent *));
#endif

extern int mallopt _PARAMS ((int, int));
#ifdef __CYGWIN__
#undef _mallopt_r
#define _mallopt_r(i1, i2) mallopt (i1, i2)
#else
extern int _mallopt_r _PARAMS ((struct _reent *, int, int));
#endif

extern size_t malloc_usable_size _PARAMS ((_PTR));
#ifdef __CYGWIN__
#undef _malloc_usable_size_r
#define _malloc_usable_size_r(r, p) malloc_usable_size (p)
#else
extern size_t _malloc_usable_size_r _PARAMS ((struct _reent *, _PTR));
#endif

/* These aren't too useful on an embedded system, but we define them
   anyhow.  */

extern _PTR valloc _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _valloc_r
#define _valloc_r(r, s) valloc (s)
#else
extern _PTR _valloc_r _PARAMS ((struct _reent *, size_t));
#endif

extern _PTR pvalloc _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _pvalloc_r
#define _pvalloc_r(r, s) pvalloc (s)
#else
extern _PTR _pvalloc_r _PARAMS ((struct _reent *, size_t));
#endif

extern int malloc_trim _PARAMS ((size_t));
#ifdef __CYGWIN__
#undef _malloc_trim_r
#define _malloc_trim_r(r, s) malloc_trim (s)
#else
extern int _malloc_trim_r _PARAMS ((struct _reent *, size_t));
#endif

/* A compatibility routine for an earlier version of the allocator.  */

extern _VOID mstats _PARAMS ((char *));
#ifdef __CYGWIN__
#undef _mstats_r
#define _mstats_r(r, p) mstats (p)
#else
extern _VOID _mstats_r _PARAMS ((struct _reent *, char *));
#endif

/* SVID2/XPG mallopt options */

#define M_MXFAST  1    /* UNUSED in this malloc */
#define M_NLBLKS  2    /* UNUSED in this malloc */
#define M_GRAIN   3    /* UNUSED in this malloc */
#define M_KEEP    4    /* UNUSED in this malloc */

#ifndef __CYGWIN__
/* Some systems provide this, so do too for compatibility.  */
extern void cfree _PARAMS ((_PTR));
#endif /* __CYGWIN__ */

#ifdef __cplusplus
}
#endif

#endif /* _INCLUDE_MALLOC_H_ */
