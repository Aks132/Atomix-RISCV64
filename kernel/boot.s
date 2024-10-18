.option norvc

.section .data
.globl hartid0   
.globl hartid1
.globl hartid2 
.globl hartid3 

hartid0:    .word 0    # Memory space for HART ID 0
hartid1:    .word 0    # Memory space for HART ID 1
hartid2:    .word 0    # Memory space for HART ID 2
hartid3:    .word 0    # Memory space for HART ID 3

# Stack space is defined and linked through the linker script

.section .text

.globl _entry



_entry:
    # Get hart ID into t0 (current core ID)
    csrr t0, mhartid   

    li t1, 0           # Check if hart is 1
    beq t0, t1, init_hart0  

    li t1, 1           # Check if hart is 1
    beq t0, t1, init_hart1  

    li t1, 2           # Check if hart is 2
    beq t0, t1, init_hart2  

    li t1, 3           # Check if hart is 3
    beq t0, t1, init_hart3  

    # If none of the above, jump to Start (default behavior)
    call Start

# Core-specific initialization, setting up their own stack

init_hart0:
    la sp, _stack_end          # Load _stack_end from linker
    li t1, 4096                # Stack size for Core 1 (subtract 8192 for Hart 1 stack)
    sub sp, sp, t1             # Adjust the stack pointer for Core 1
    la t1, hartid1             # Store hart ID in data memory (for Core 1)
    sw t0, 0(t1)
    j Core0_Init            # Call core-specific initialization function
   

init_hart1:
    la sp, _stack_end          # Load _stack_end from linker
    li t1, 8192                # Stack size for Core 1 (subtract 8192 for Hart 1 stack)
    sub sp, sp, t1             # Adjust the stack pointer for Core 1
    la t1, hartid1             # Store hart ID in data memory (for Core 1)
    sw t0, 0(t1)
    j Core1_Init            # Call core-specific initialization function
   

init_hart2:
    la sp, _stack_end          # Load _stack_end from linker
    li t1, 12288               # Stack size for Core 2 (subtract 12288 for Hart 2 stack)
    sub sp, sp, t1             # Adjust the stack pointer for Core 2
    la t1, hartid2             # Store hart ID in data memory (for Core 2)
    sw t0, 0(t1)
    j Core2_Init            # Call core-specific initialization function
   

init_hart3:
    la sp, _stack_end          # Load _stack_end from linker
    li t1, 16384               # Stack size for Core 3 (subtract 16384 for Hart 3 stack)
    sub sp, sp, t1             # Adjust the stack pointer for Core 3
    la t1, hartid3             # Store hart ID in data memory (for Core 3)
    sw t0, 0(t1)
    j Core3_Init            # Call core-specific initialization function
   