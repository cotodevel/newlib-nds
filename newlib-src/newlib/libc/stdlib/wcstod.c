/*
FUNCTION
        <<wcstod>>, <<wcstof>>---wide char string to double or float

INDEX
	wcstod
INDEX
	_wcstod_r
INDEX
	wcstof
INDEX
	_wcstof_r

ANSI_SYNOPSIS
        #include <stdlib.h>
        double wcstod(const wchar_t *__restrict <[str]>,
            wchar_t **__restrict <[tail]>);
        float wcstof(const wchar_t *__restrict <[str]>,
            wchar_t **__restrict <[tail]>);

        double _wcstod_r(void *<[reent]>,
                         const wchar_t *<[str]>, wchar_t **<[tail]>);
        float _wcstof_r(void *<[reent]>,
                         const wchar_t *<[str]>, wchar_t **<[tail]>);

TRAD_SYNOPSIS
        #include <stdlib.h>
        double wcstod(<[str]>,<[tail]>)
        wchar_t *__restrict <[str]>;
        wchar_t **__restrict <[tail]>;

        float wcstof(<[str]>,<[tail]>)
        wchar_t *__restrict <[str]>;
        wchar_t **__restrict <[tail]>;

        double _wcstod_r(<[reent]>,<[str]>,<[tail]>)
	wchar_t *<[reent]>;
        wchar_t *<[str]>;
        wchar_t **<[tail]>;

        float _wcstof_r(<[reent]>,<[str]>,<[tail]>)
	wchar_t *<[reent]>;
        wchar_t *<[str]>;
        wchar_t **<[tail]>;

DESCRIPTION
	The function <<wcstod>> parses the wide character string <[str]>,
	producing a substring which can be converted to a double
	value.  The substring converted is the longest initial
	subsequence of <[str]>, beginning with the first
	non-whitespace character, that has one of these formats:
	.[+|-]<[digits]>[.[<[digits]>]][(e|E)[+|-]<[digits]>]
	.[+|-].<[digits]>[(e|E)[+|-]<[digits]>]
	.[+|-](i|I)(n|N)(f|F)[(i|I)(n|N)(i|I)(t|T)(y|Y)]
	.[+|-](n|N)(a|A)(n|N)[<(>[<[hexdigits]>]<)>]
	.[+|-]0(x|X)<[hexdigits]>[.[<[hexdigits]>]][(p|P)[+|-]<[digits]>]
	.[+|-]0(x|X).<[hexdigits]>[(p|P)[+|-]<[digits]>]
	The substring contains no characters if <[str]> is empty, consists
	entirely of whitespace, or if the first non-whitespace
	character is something other than <<+>>, <<->>, <<.>>, or a
	digit, and cannot be parsed as infinity or NaN. If the platform
	does not support NaN, then NaN is treated as an empty substring.
	If the substring is empty, no conversion is done, and
	the value of <[str]> is stored in <<*<[tail]>>>.  Otherwise,
	the substring is converted, and a pointer to the final string
	(which will contain at least the terminating null character of
	<[str]>) is stored in <<*<[tail]>>>.  If you want no
	assignment to <<*<[tail]>>>, pass a null pointer as <[tail]>.
	<<wcstof>> is identical to <<wcstod>> except for its return type.

	This implementation returns the nearest machine number to the
	input decimal string.  Ties are broken by using the IEEE
	round-even rule.  However, <<wcstof>> is currently subject to
	double rounding errors.

	The alternate functions <<_wcstod_r>> and <<_wcstof_r>> are 
	reentrant versions of <<wcstod>> and <<wcstof>>, respectively.
	The extra argument <[reent]> is a pointer to a reentrancy structure.

RETURNS
	Return the converted substring value, if any.  If
	no conversion could be performed, 0 is returned.  If the
	correct value is out of the range of representable values,
	plus or minus <<HUGE_VAL>> is returned, and <<ERANGE>> is
	stored in errno. If the correct value would cause underflow, 0
	is returned and <<ERANGE>> is stored in errno.

Supporting OS subroutines required: <<close>>, <<fstat>>, <<isatty>>,
<<lseek>>, <<read>>, <<sbrk>>, <<write>>.
*/

/*-
 * Copyright (c) 2002 Tim J. Robbins
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <_ansi.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
double
_DEFUN (_wcstod_r, (ptr, nptr, endptr),
	struct _reent *ptr _AND
	_CONST wchar_t *nptr _AND
	wchar_t **endptr)
{
        static const mbstate_t initial;
        mbstate_t mbs;
        double val;
        char *buf, *end;
        const wchar_t *wcp;
        size_t len;

        while (iswspace(*nptr))
                nptr++;

        /*
         * Convert the supplied numeric wide char. string to multibyte.
         *
         * We could attempt to find the end of the numeric portion of the
         * wide char. string to avoid converting unneeded characters but
         * choose not to bother; optimising the uncommon case where
         * the input string contains a lot of text after the number
         * duplicates a lot of strtod()'s functionality and slows down the
         * most common cases.
         */
        wcp = nptr;
        mbs = initial;
        if ((len = _wcsrtombs_r(ptr, NULL, &wcp, 0, &mbs)) == (size_t)-1) {
                if (endptr != NULL)
                        *endptr = (wchar_t *)nptr;
                return (0.0);
        }
        if ((buf = _malloc_r(ptr, len + 1)) == NULL)
                return (0.0);
        mbs = initial;
        _wcsrtombs_r(ptr, buf, &wcp, len + 1, &mbs);

        /* Let strtod() do most of the work for us. */
        val = _strtod_r(ptr, buf, &end);

        /*
         * We only know where the number ended in the _multibyte_
         * representation of the string. If the caller wants to know
         * where it ended, count multibyte characters to find the
         * corresponding position in the wide char string.
         */
        if (endptr != NULL) {
		/* The only valid multibyte char in a float converted by
		   strtod/wcstod is the radix char.  What we do here is,
		   figure out if the radix char was in the valid leading
		   float sequence in the incoming string.  If so, the
		   multibyte float string is strlen(radix char) - 1 bytes
		   longer than the incoming wide char string has characters.
		   To fix endptr, reposition end as if the radix char was
		   just one byte long.  The resulting difference (end - buf)
		   is then equivalent to the number of valid wide characters
		   in the input string. */
		len = strlen (_localeconv_r (ptr)->decimal_point);
		if (len > 1) {
			char *d = strstr (buf,
					  _localeconv_r (ptr)->decimal_point);
			if (d && d < end)
				end -= len - 1;
		}
                *endptr = (wchar_t *)nptr + (end - buf);
	}

        _free_r(ptr, buf);

        return (val);
}

float
_DEFUN (_wcstof_r, (ptr, nptr, endptr),
	struct _reent *ptr _AND
	_CONST wchar_t *nptr _AND
	wchar_t **endptr)
{
  double retval = _wcstod_r (ptr, nptr, endptr);
  if (isnan (retval))
    return nanf (NULL);
  return (float)retval;
}

#ifndef _REENT_ONLY

double
_DEFUN (wcstod, (nptr, endptr),
	_CONST wchar_t *__restrict nptr _AND wchar_t **__restrict endptr)
{
  return _wcstod_r (_REENT, nptr, endptr);
}

float
_DEFUN (wcstof, (nptr, endptr),
	_CONST wchar_t *__restrict nptr _AND
	wchar_t **__restrict endptr)
{
  double retval = _wcstod_r (_REENT, nptr, endptr);
  if (isnan (retval))
    return nanf (NULL);
  return (float)retval;
}

#endif
