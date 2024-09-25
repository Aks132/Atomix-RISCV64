all:
	make asm
	make c
	make link
asm:
	riscv64-unknown-elf-as boot.s -o boot.o
c:
	riscv64-unknown-elf-gcc -mcmodel=medany start.c -c -o start.o
	riscv64-unknown-elf-gcc -mcmodel=medany /Users/deveshshevde/RISC-V/Include/uart.c -c -o uart.o
	riscv64-unknown-elf-gcc -mcmodel=medany /Users/deveshshevde/RISC-V/Include/libc/Wprintf.c -c -o print.o
link:
	riscv64-unknown-elf-ld -T linker.ld boot.o start.o print.o uart.o -o kernel.elf
qemu:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4  -m 128 -nographic -serial mon:stdio -bios none  -kernel kernel.elf
clean:
	rm *.o *.elf
