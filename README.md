# Atomix-RISCV64

Atomix-RISCV64 is an operating system built from scratch targeting the RISC-V 64-bit architecture. The project focuses on learning, implementing fundamental OS concepts, and enabling multi-hart support in a bare-metal environment. It uses the RISC-V GNU toolchain for development and QEMU for emulation on macOS.

## RISC-V GNU Toolchain Installation on macOS

This guide explains how to install the RISC-V GNU toolchain on macOS using Homebrew, allowing you to develop and run RISC-V programs in an emulated environment.

### Prerequisites

Before starting, ensure that you have the following:

- macOS system with command line tools installed.
- [Homebrew](https://brew.sh) package manager installed.

### Install for MacOS
Open the Terminal and paste the following command:

```bash
git clone https://github.com/Aks132/RISC-V.git
cd RISC-V
```
```bash
chmod +x mac-setup.sh
sh mac-setup.sh
```

### Install for Ubuntu
Open the Terminal and paste the following command:

```bash
git clone https://github.com/Aks132/RISC-V.git
cd RISC-V
```
```bash
chmod +x ubuntu-setup.sh
sh ubuntu-setup.sh
```

### Verify the Installation

You can now verify that the toolchain is properly installed and accessible by running the following commands:

```bash
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-as --version
```

If the toolchain is set up correctly, you should see version information for both commands.

## References
- [The RISC-V Instruction Set Manual Volume I: User-Level ISA ](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
- [The RISC-V Instruction Set Manual Volume II: Privileged Architecture. ](https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf)
- [OpenSBI Deep Dive](https://riscv.org/wp-content/uploads/2019/06/13.30-RISCV_OpenSBI_Deep_Dive_v5.pdf)
- [xv6: a simple, Unix-like teaching operating system](https://pdos.csail.mit.edu/6.828/2022/xv6/book-riscv-rev3.pdf)


## TODO;
- [ ] Core Locking
- [ ] Memory Mapping

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.