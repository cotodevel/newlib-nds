#ifndef _IOLIBIO_H
#define _IOLIBIO_H 1

#include <stdio.h>
//#include <libio.h>

#define _IO_clearerr(FP) ((FP)->_flags &= ~(_IO_ERR_SEEN|_IO_EOF_SEEN))
#define _IO_fseek(__fp, __offset, __whence) \
  (_IO_seekoff_unlocked (__fp, __offset, __whence, _IOS_INPUT|_IOS_OUTPUT) \
   == _IO_pos_BAD ? EOF : 0)
#define _IO_rewind(FILE) \
  (void) _IO_seekoff_unlocked (FILE, 0, 0, _IOS_INPUT|_IOS_OUTPUT)
#define _IO_vprintf(FORMAT, ARGS) \
  _IO_vfprintf (_IO_stdout, FORMAT, ARGS)
#define _IO_freopen(FILENAME, MODE, FP) \
  (_IO_file_close_it (FP), \
   _IO_file_fopen (FP, FILENAME, MODE, 1))
#define _IO_old_freopen(FILENAME, MODE, FP) \
  (_IO_old_file_close_it (FP), _IO_old_file_fopen(FP, FILENAME, MODE))
#define _IO_freopen64(FILENAME, MODE, FP) \
  (_IO_file_close_it (FP), \
   _IO_file_fopen (FP, FILENAME, MODE, 0))
#define _IO_fileno(FP) ((FP)->_fileno)
#define _IO_pclose _IO_fclose
#define _IO_setbuf(_FP, _BUF) _IO_setbuffer (_FP, _BUF, BUFSIZ)
#define _IO_setlinebuf(_FP) _IO_setvbuf (_FP, NULL, 1, 0)

FILE *__new_freopen (const char *, const char *, FILE *) __THROW;
FILE *__old_freopen (const char *, const char *, FILE *) __THROW;

#endif /* iolibio.h.  */