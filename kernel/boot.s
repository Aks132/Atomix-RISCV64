/*Dont generate 16 bit instructions*/

.option norvc
.section .data
.globl hartid0   
.globl hartid1
.globl hartid2 
.globl hartid3 

hartid0:    .word 0    # Memory space for HART ID 0
hartid1:    .word 0    # Memory space for HART ID 0
hartid2:    .word 0    # Memory space for HART ID 1
hartid3:    .word 0    # Memory space for HART ID 2

      

.section .text

.globl _entry

.extern main
.extern Core0_Init
.extern Core1_Init
.extern Core2_Init
.extern Core3_Init
  
_entry:

    la sp , _stack_end
    csrr t0, mhartid   
    li t1, 0           
    beq t0, t1, init_hart0  
    li t1, 1
    beq t0, t1, init_hart1  
    li t1, 2
    beq t0, t1, init_hart2  
    li t1, 3
    beq t0, t1, init_hart3  
    j main


init_hart0:
    la t1, hartid0         
    sw t0, 0(t1)           
    j Core0_Init                 

init_hart1:
    la t1, hartid1        
    sw t0, 0(t1)           
    j Core1_Init                 

init_hart2:
    la t1, hartid2         
    sw t0, 0(t1)          
    j Core2_Init                

init_hart3:
    la t1, hartid3        
    sw t0, 0(t1)         
    j Core3_Init               




_loop:
    j main
.end
