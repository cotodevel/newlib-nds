#ifndef __ioctl_h
#define __ioctl_h

#include "typedefsTGDS.h"

#include <sys/types.h>
#include <sys/_types.h>
#include <in.h>
#include <netdb.h>



//these from in.h (linux) but dswifi already has one, merge them later
/* Protocols common to RFC 1700, POSIX, and X/Open. */
#define	IPPROTO_IP		0		/* dummy for IP */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_UDP		17		/* user datagram protocol */

typedef unsigned short sa_family_t;





//these from inet.h
#ifndef __socklen_t_defined
typedef unsigned int socklen_t;
#define __socklen_t_defined 1
#endif


//these from netdb.h
#define	MAXALIASES	35
  /* For now, only support one return address. */
#define MAXADDRS         2

//use dswifi for specific ioctl.h interface

#endif