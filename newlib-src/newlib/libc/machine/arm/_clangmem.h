#ifndef __clangmem
#define __clangmem

#include <string.h>
#include <stdio.h>
#include <typedefsTGDS.h>

#ifdef __cplusplus
extern "C"{
#endif

extern void __aeabi_memset(void *dest, size_t n, int c);
extern void __aeabi_memset4(void *dest, size_t n, int c);
extern void __aeabi_memset8(void *dest, size_t n, int c);

extern void __aeabi_memclr(void *dest, size_t n);
extern void __aeabi_memcpy(void *dest, void *src, size_t n);
extern void __aeabi_memmove (void *dest, const void *src, size_t n);
extern uint64_t __aeabi_lmul(uint32_t a, uint32_t b);

#ifdef __cplusplus
}
#endif


#endif