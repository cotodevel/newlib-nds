#include <string.h>
#include <stdio.h>

#include "_clangmem.h"

uint64_t __aeabi_lmul(uint32_t a, uint32_t b){
    uint32_t hia = a >> 16,
        hib = b >> 16,
        loa = (uint32_t)(uint16_t)a,
        lob = (uint32_t)(uint16_t)b,
        low = loa * lob,
        mid1 = hia * lob,
        mid2 = loa * hib,
        mid = mid1 + mid2,
        high = hia * hib;

    if (mid < mid1)
        high += 0x10000;
    return ((uint64_t)high << 32) + ((uint64_t)mid << 16) + low;
}