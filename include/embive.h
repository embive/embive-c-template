#ifndef EMBIVE_H
#define EMBIVE_H

typedef struct {
    int val1;
    int val2;
} SyscallReturn_t;

// System Call. Check [syscall(2)](https://man7.org/linux/man-pages/man2/syscall.2.html). Must be implemented by the host.
SyscallReturn_t syscall(int nr, int a0, int a1, int a2, int a3, int a4, int a5);

#endif