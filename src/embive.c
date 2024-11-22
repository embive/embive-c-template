#include "embive.h"

extern unsigned int __bss_target_start; // Start of .bss target
extern unsigned int __bss_target_end; // End of .bss target
extern unsigned int __data_target_start; // Start of .data target
extern unsigned int __data_target_end; // End of .data target
extern unsigned int __data_source_start; // Start of .data source
extern void main(void);

// System Call. Must be implemented by the host.
SyscallResult_t syscall(int nr, int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    SyscallResult_t ret;

    register long ra0 asm("a0") = a0;
    register long ra1 asm("a1") = a1;
    register long ra2 asm("a2") = a2;
    register long ra3 asm("a3") = a3;
    register long ra4 asm("a4") = a4;
    register long ra5 asm("a5") = a5;
    register long ra6 asm("a6") = a6;
    register long ra7 asm("a7") = nr;

    __asm__ volatile ("ecall"
        : "+r"(ra0), "+r"(ra1)
        : "r"(ra2), "r"(ra3), "r"(ra4), "r"(ra5), "r"(ra6), "r"(ra7));
    
    ret.error = ra0;
    ret.value = ra1;

    return ret;
}

// This code is responsible for initializing the .bss and .data sections, and calling the user's main function.
void _code_entry(void)
{
    unsigned int *src, *dst;

    // Initialize .bss section
    for (dst = &__bss_target_start; dst < &__bss_target_end; dst++)
        *dst = 0;

    // Initialize .data section
    for (src = &__data_source_start, dst = &__data_target_start; dst < &__data_target_end; src++, dst++)
        *dst = *src;

    // Call user's main function
    main();

    // Exit the interpreter
    __asm__ volatile ("ebreak");

    __builtin_unreachable();
}
