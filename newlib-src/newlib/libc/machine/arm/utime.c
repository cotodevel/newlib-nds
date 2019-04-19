#include <errno.h>
#include <utime.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>


/* Set the access and modification times of FILE to those given in TIMES.
If TIMES is NULL, set them to the current time.  */
int
utime (const char *file, const struct utimbuf *times)
{
	struct timeval timevals[2];
	struct timeval *tvp;

	if (times != NULL)
	{
	timevals[0].tv_sec = (time_t) times->actime;
	timevals[0].tv_usec = 0L;
	timevals[1].tv_sec = (time_t) times->modtime;
	timevals[1].tv_usec = 0L;
	tvp = timevals;
	}
	else
	tvp = NULL;

	//return __utimes(file, tvp);		//todo
	return -1;
}
