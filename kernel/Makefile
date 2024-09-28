# Variables for toolchain and directories
CROSS_COMPILE = riscv64-unknown-elf-
INCLUDE_DIR = ../include
LIBC_DIR = $(INCLUDE_DIR)/libc

# Compiler and linker flags
CFLAGS = -mcmodel=medany -O -I$(INCLUDE_DIR) -I$(LIBC_DIR) 

# Targets
all: asm c link

asm:
	$(CROSS_COMPILE)as boot.s -o boot.o

c:
	$(CROSS_COMPILE)gcc $(CFLAGS) start.c -c -o start.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(LIBC_DIR)/Wprintf.c -c -o print.o
	$(CROSS_COMPILE)gcc $(CFLAGS) main.c -c -o main.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/uart.c -c -o uart.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/mutex.c -c -o mutex.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/core.c -c -o core.o

link:
	$(CROSS_COMPILE)ld -T linker.ld boot.o start.o print.o uart.o mutex.o main.o core.o -o kernel.elf

qemu:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4  -m 128 -nographic -serial mon:stdio -bios none  -kernel kernel.elf

clean:
	rm -f *.o *.elf
