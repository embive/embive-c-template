#include "embive.h"

const int CONST_DATA = 20;
static int GLOBAL_DATA = 10;

// User's main function
// This is a simple example of a program that runs in the Embive interpreter
// Here, we are calling two system calls, one to get a value from a memory address and another to add two numbers
// The system calls must be implemented in the host application (check Embive example)
void main(void)
{
    SyscallResult_t res;
    // System Call 2: Get i32 value at address
    // The host will receive the GLOBAL_DATA address, read it from memory and return its value
    res = syscall(2, (int) &GLOBAL_DATA, 0, 0, 0, 0, 0, 0);

    // Do something here

    if (res.error == 0) {
        // System Call 1: Add two numbers (a0 + a1)
        res = syscall(1, res.value, CONST_DATA, 0, 0, 0, 0, 0);
    }
}