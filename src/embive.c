#include "embive.h"

extern unsigned int _bss_target_start; // Start of .bss target
extern unsigned int _bss_target_end; // End of .bss target
extern unsigned int _data_target_start; // Start of .data target
extern unsigned int _data_target_end; // End of .data target
extern unsigned int _data_source_start; // Start of .data source
extern void _entry(void)  __attribute__ ((naked, section(".text.init.entry"))); // Entry point

extern void main(void);

// System Call. Check [syscall(2)](https://man7.org/linux/man-pages/man2/syscall.2.html). Must be implemented by the host.
SyscallReturn_t syscall(int nr, int a0, int a1, int a2, int a3, int a4, int a5) {
    SyscallReturn_t ret;

    register long ra0 asm("a0") = a0;
    register long ra1 asm("a1") = a1;
    register long ra2 asm("a2") = a2;
    register long ra3 asm("a3") = a3;
    register long ra4 asm("a4") = a4;
    register long ra5 asm("a5") = a5;
    register long ra7 asm("a7") = nr;

    asm volatile ("scall"
		: "+r"(ra0) : "r"(ra1), "r"(ra2), "r"(ra3), "r"(ra4), "r"(ra5), "r"(ra7));
    
    ret.val1 = ra0;
    ret.val2 = ra1;

    return ret;
}

// Code execution starts here. Embive initializes the stack pointer and jumps to this address.
// This code is responsible for initializing the .bss and .data sections and calling the user's main function.
void _entry(void)
{
    unsigned int *src, *dst;

    // Initialize .bss section
    for (dst = &_bss_target_start; dst < &_bss_target_end; dst++)
    {
        *dst = 0;
    }

    // Initialize .data section
    for (src = &_data_source_start, dst = &_data_target_start; dst < &_data_target_end; src++, dst++)
    {
        *dst = *src;
    }

    // Call user's main function
    main();

    // Exit the interpreter
    __asm__ volatile ("ebreak");

    // Should never get here
    while (1) {}
}