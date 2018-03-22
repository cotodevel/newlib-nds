#if defined(__ARM_EABI__)
int
__aeabi_idiv0(int return_value) {
 return return_value;
}

long long __attribute__((weak)) __attribute__((visibility("hidden")))
__aeabi_ldiv0(long long return_value) {
return return_value;
}
#endif

