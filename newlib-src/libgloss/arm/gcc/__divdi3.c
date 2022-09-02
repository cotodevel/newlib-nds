#ifdef ARM9

#include "typedefsTGDS.h"

#define DIV_CR				(*(vuint16*)(0x04000280))
#define DIV_NUMERATOR64		(*(vsint64*) (0x04000290))
#define DIV_NUMERATOR32		(*(vsint32*) (0x04000290))
#define DIV_DENOMINATOR64	(*(vsint64*) (0x04000298))
#define DIV_DENOMINATOR32	(*(vsint32*) (0x04000298))
#define DIV_RESULT64		(*(vsint64*) (0x040002A0))
#define DIV_RESULT32		(*(vsint32*) (0x040002A0))
#define DIV_REMANDER64		(*(vsint64*) (0x040002A8))
#define DIV_REMANDER32		(*(vsint32*) (0x040002A8))

#define DIV_64_64			2
#define DIV_64_32			1
#define DIV_32_32			0
#define DIV_BUSY			(1<<15)

#endif

/*
 * __divsi3.c for 64-bit signed integer divide.
 */

extern unsigned long long __udivmoddi4(unsigned long long num, unsigned long long den, unsigned long long * rem_p);

/*
 * 64-bit signed integer divide.
 */
signed long long __divdi3(signed long long num, signed long long den){
	#ifdef ARM7
	signed int minus = 0;
	signed long long v;

	if (num < 0)
	{
		num = -num;
		minus = 1;
	}
	if (den < 0)
	{
		den = -den;
		minus ^= 1;
	}

	v = __udivmoddi4(num, den, 0);
	if (minus)
		v = -v;

	return v;
	#endif
	
	#ifdef ARM9
	DIV_CR = DIV_64_64;
	//while(DIV_CR & DIV_BUSY);
	DIV_NUMERATOR64 = num;
	DIV_DENOMINATOR64 = den;
	while(DIV_CR & DIV_BUSY);
	return (DIV_RESULT64);
	#endif
}
