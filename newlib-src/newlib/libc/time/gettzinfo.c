#include <sys/types.h>
#include <local.h>

typedef struct __tzrule_struct
{
  char ch;
  int m;
  int n;
  int d;
  int s;
  time_t change;
  long offset; /* Match type of _timezone. */
} __tzrule_type;

typedef struct __tzinfo_struct
{
  int __tznorth;
  int __tzyear;
  __tzrule_type __tzrule[2];
} __tzinfo_type;


/* Shared timezone information for libc/time functions.  */
static __tzinfo_type tzinfo = {1, 0,
    { {'J', 0, 0, 0, 0, (time_t)0, 0L },
      {'J', 0, 0, 0, 0, (time_t)0, 0L } 
    } 
};

__tzinfo_type *
__gettzinfo (void)
{
  return &tzinfo;
}
