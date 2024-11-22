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

// System Call. Must be implemented by the host.
SyscallResult_t syscall(int nr, int a0, int a1, int a2, int a3, int a4, int a5, int a6);

#ifdef __cplusplus
}
#endif
#endif