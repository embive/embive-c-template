#ifndef EMBIVE_H
#define EMBIVE_H
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    int error;
    int value;
} SyscallResult_t;

// Wait For Interrupt
//
// Ask the host to put the interpreter to sleep until an interruption occurs
// May return without any interruption.
inline void wfi(void)
{
    __asm__ volatile ("wfi");
}

// Exit the interpreter
inline void ebreak(void)
{
    __asm__ volatile ("ebreak");
}

// Enable Interrupts
//
// Set the `mstatus.MIE` bit to 1
inline void enable_interrupts(void)
{
    __asm__ volatile ("csrsi mstatus, 8");
}

// Disable Interrupts
//
// Set the `mstatus.MIE` bit to 0
inline void disable_interrupts(void)
{
    __asm__ volatile ("csrci mstatus, 8");
}

// System Call. Must be implemented by the host.
SyscallResult_t syscall(int nr, int a0, int a1, int a2, int a3, int a4, int a5, int a6);

#ifdef __cplusplus
}
#endif
#endif