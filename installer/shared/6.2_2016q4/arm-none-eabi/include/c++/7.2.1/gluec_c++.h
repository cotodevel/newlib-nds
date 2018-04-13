#ifndef __glue_c_cpp
#define __glue_c_cpp

#include <reent.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

namespace std{
	
	extern "C" long double wcstold(const wchar_t *, wchar_t **);
	extern "C" long double strtold(const char *, char **);
	
	extern "C" long double acoshl(long double x);
	
	extern "C" long double asinhl(long double x);
	
	extern "C" long double atanhl (long double x);
	
	extern "C" long double cbrtl(long double x);
	
	extern "C" long double copysignl(long double x, long double y);
	
	extern "C" long double erfl(long double x);
	
	extern "C" long double erfcl(long double x);
	
	extern "C" long double exp2l(long double x);
	
	extern "C" long double expm1l(long double x);
	
	extern "C" long double fdiml(long double x, long double y);
	
	extern "C" long double fmal(long double x, long double y, long double z);
	
	extern "C" long double fmaxl (long double x, long double y);
	
	extern "C" long double fminl(long double x, long double y);
	
	extern "C" int ilogbl(long double x);
	
	extern "C" long double lgammal(long double x);
	
	extern "C" long long int llrintl(long double x);
	
	extern "C" long long int llroundl(long double x);
	
	extern "C" long double log1pl(long double x);
	
	extern "C" long double log2l(long double x);
	
	extern "C" long double logbl(long double x);
	
	extern "C" long int lrintl(long double x);
	
	extern "C" long lroundl(long double x);
	
	extern "C" long double nanl(const char *tagp);
	
	extern "C" long double nearbyintl(long double x);
	
	extern "C" long double nextafterl(long double x, long double y);
	
	extern "C" double nexttoward(double x, long double y);
	
	extern "C" float nexttowardf(float x, long double y);
	
	extern "C" long double nexttowardl(long double x, long double y);
	
	extern "C" long double remainderl(long double x, long double p);
	
	extern "C" long double remquol(long double x, long double y, int *quo);
	
	extern "C" long double rintl(long double x);
	
	extern "C" long double roundl(long double x);
	
	extern "C" long double scalblnl(long double x, long n);
	
	extern "C" long double scalbnl(long double x, int n);
	
	extern "C" long double tgammal(long double x);
	
	extern "C" long double truncl(long double x);
	
	extern "C" int wctob(wint_t wc);
	
}

#endif