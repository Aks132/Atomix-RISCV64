all:
	make asm
	make c
	make link
asm:
	riscv64-unknown-elf-as boot.s -o boot.o
c:
	riscv64-unknown-elf-gcc -mcmodel=medany start.c -c -o start.o
link:
	riscv64-unknown-elf-ld -T linker.ld boot.o start.o -o kernel.elf 
qemu:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4  -m 128 -nographic -serial mon:stdio -bios none  -kernel kernel.elf 
clean:
	rm *.o *.elf