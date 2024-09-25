/*Dont generate 16 bit instructions*/

.option norvc

.section .data

.section .text.init

.globl _entry
.extern main

_entry:

    la sp , _stack_end
    jal main

.end