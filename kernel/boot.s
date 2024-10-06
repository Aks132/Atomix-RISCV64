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

    # Store the hart ID into the appropriate memory space
    la t1, hartid0            # Base address for hartid storage
    li a0, 4                  # Word size (each hartid is 4 bytes apart)
    mul a0, t0, a0            # Calculate the correct offset for this hart
    add t1, t1, a0            # Compute the hartidX address
    sw t0, 0(t1)              # Store hart ID at calculated address

    # Set up the stack for the hart
    la sp, stack0             # Load base address of stack0 (defined in start.c)
    li a0, 1024*4             # Stack size per hart (4KB)
    csrr a1, mhartid          # Get hart ID again into a1
    mul a0, a0, a1            # Calculate offset: hartid * 4KB
    add sp, sp, a0            # Set up stack pointer for this hart

    # Jump to start function in C
    call start

spin:
    j spin                    # Infinite loop after start to prevent further execution
