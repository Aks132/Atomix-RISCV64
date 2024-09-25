all:
	riscv64-unknown-elf-as boot.s -o boot.o

link:
	riscv64-unknown-elf-ld -T linker.ld boot.o -o kernel.elf
qemu:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4  -m 128 -nographic -serial mon:stdio -bios none  -kernel kernel.elf 