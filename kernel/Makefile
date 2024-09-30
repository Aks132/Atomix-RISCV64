# Variables for toolchain and directories
CROSS_COMPILE = riscv64-unknown-elf-
INCLUDE_DIR = ../include
BUILD_DIR = ../build
LIBC_DIR = $(INCLUDE_DIR)/libc

# Compiler and linker flags
CFLAGS = -mcmodel=medany -O -I$(INCLUDE_DIR) -I$(LIBC_DIR)

# Targets
all: asm c link

asm:
	$(CROSS_COMPILE)as boot.s -o $(BUILD_DIR)/boot.o

c:
	$(CROSS_COMPILE)gcc $(CFLAGS) start.c -c -o $(BUILD_DIR)/start.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(LIBC_DIR)/Wprintf.c -c -o $(BUILD_DIR)/print.o
	$(CROSS_COMPILE)gcc $(CFLAGS) main.c -c -o $(BUILD_DIR)/main.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/uart/uart.c -c -o $(BUILD_DIR)/uart.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/mutex/mutex.c -c -o $(BUILD_DIR)/mutex.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/core/core.c -c -o $(BUILD_DIR)/core.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/memAlloc.c -c -o $(BUILD_DIR)/memAlloc.o
	$(CROSS_COMPILE)gcc $(CFLAGS) $(INCLUDE_DIR)/syscon/syscon.c -c -o $(BUILD_DIR)/syscon.o


link:
	$(CROSS_COMPILE)ld -T linker.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/print.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/mutex.o $(BUILD_DIR)/memAlloc.o $(BUILD_DIR)/core.o $(BUILD_DIR)/syscon.o $(BUILD_DIR)/start.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/kernel.elf -Map $(BUILD_DIR)/kernel.map

qemu:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4  -m 128 -nographic -serial mon:stdio -bios none  -kernel $(BUILD_DIR)/kernel.elf

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.map
