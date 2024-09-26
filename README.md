# RISC-V GNU Toolchain Installation on macOS

This guide explains how to install the RISC-V GNU toolchain on macOS using Homebrew, allowing you to develop and run RISC-V programs in an emulated environment.

## Prerequisites

Before starting, ensure that you have the following:

- macOS system with command line tools installed.
- [Homebrew](https://brew.sh) package manager installed.

## Install for MacOS
Open the Terminal and paste the following command:

```bash
git clone https://github.com/Aks132/RISC-V.git
cd RISC-V
```
```bash
chmod +x mac-setup.sh
sh mac-setup.sh
```


## Verify the Installation

You can now verify that the toolchain is properly installed and accessible by running the following commands:

```bash
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-as --version
```

If the toolchain is set up correctly, you should see version information for both commands.
