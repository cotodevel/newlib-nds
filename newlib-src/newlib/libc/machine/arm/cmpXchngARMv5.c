#ifdef ARM9

#include "typedefsTGDS.h"

static char q_atomic_lock = 0;

static inline char q_atomic_swp(volatile char *ptr, char newval)
{
    register int ret;
    asm volatile("swpb %0,%1,[%2]"
                 : "=&r"(ret)
                 : "r"(newval), "r"(ptr)
                 : "cc", "memory");
    return ret;
}

int q_atomic_test_and_set_int(volatile int *ptr, int expected, int newval){
    int ret = 0;
    while (q_atomic_swp(&q_atomic_lock, ~0) != 0);
    if (*ptr == expected) {
	*ptr = newval;
	ret = 1;
    }
    q_atomic_swp(&q_atomic_lock, 0);
    return ret;
}

//Clang doesn't let me redefine this builtin required by C++ code so, use GCC instead
/*
uint32 __sync_val_compare_and_swap_1(volatile uint32* ptr, uint32 oldval, uint32 newval){	//same as cmpchg(...);
	return q_atomic_test_and_set_int((volatile int *)ptr, oldval, newval);
}
*/

#endif