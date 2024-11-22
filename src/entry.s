.section .text.init.entry, "ax"
.global _entry

_entry:
    /* Initialize global pointer */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    /* Initialize stack and frame pointers */
    la t1, __stack_start
    andi sp, t1, -16
    add s0, sp, zero
    /* Call _code_entry */
    jal ra, _code_entry
