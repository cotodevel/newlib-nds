#include "asmclang.h"

//  void __aeabi_memset(void *dest, size_t n, int c) { memset(dest, c, n); }
//  void __aeabi_memclr(void *dest, size_t n) { __aeabi_memset(dest, n, 0); }

        .p2align 4
DEFINE_COMPILERRT_FUNCTION(__aeabi_memset)
        mov     r3, r1
        mov     r1, r2
        mov     r2, r3
        b       memset
END_COMPILERRT_FUNCTION(__aeabi_memset)

DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memset4, __aeabi_memset)
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memset8, __aeabi_memset)

DEFINE_COMPILERRT_FUNCTION(__aeabi_memclr)
        mov     r2, r1
        mov     r1, #0
        b       memset
END_COMPILERRT_FUNCTION(__aeabi_memclr)

DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memclr4, __aeabi_memclr)
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memclr8, __aeabi_memclr)


//  void __aeabi_memcpy(void *dest, void *src, size_t n) { memcpy(dest, src, n); }
        .align 4
DEFINE_COMPILERRT_FUNCTION(__aeabi_memcpy)
        b       memcpy
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcpy4, __aeabi_memcpy)
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcpy8, __aeabi_memcpy)


//  void __aeabi_memmove(void *dest, void *src, size_t n) { memmove(dest, src, n); }
        .align 4
DEFINE_COMPILERRT_FUNCTION(__aeabi_memmove)
        b       memmove
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memmove4, __aeabi_memmove)
DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memmove8, __aeabi_memmove)


#ifdef ARM9
//  uint32 __sync_val_compare_and_swap(volatile uint32* ptr, uint32 oldval, uint32 newval);
        .align 4
DEFINE_COMPILERRT_FUNCTION(__sync_val_compare_and_swap)
        b       q_atomic_test_and_set_int
DEFINE_AEABI_FUNCTION_ALIAS(__sync_val_compare_and_swap_1, __sync_val_compare_and_swap)
DEFINE_AEABI_FUNCTION_ALIAS(__sync_val_compare_and_swap_2, __sync_val_compare_and_swap)
#endif