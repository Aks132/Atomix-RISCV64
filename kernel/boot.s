/*Dont generate 16 bit instructions*/

.option norvc



.section .text

.globl _entry
.extern main

_entry:

    la sp , _stack_end
    csrr t0 , mhartid
    bnez t0 , _loop
    j main

_loop:
    j _loop
.end
