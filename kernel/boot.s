/*Dont generate 16 bit instructions*/

.option norvc
.section .data
.globl hartid   # Declare the global variable hartid
hartid:
    .word 0         # Define hartid and initialize it to 0

.section .text

.globl _entry

.extern main
  
_entry:

    la sp , _stack_end
    csrr t0 , mhartid
    la t1, hartid           # Load address of hartid into t1
    sw t0, 0(t1)            # Store value from t0 into the memory address of hartid
    bnez t0 , _loop
    j main

_loop:
    j _loop
.end
