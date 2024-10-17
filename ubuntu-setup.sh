#!/bin/bash

# RISC-V GNU Toolchain Installation Script for Ubuntu/Linux

# Enable exit on error
set -e

# Step 1: Update and Install Prerequisites
echo "Updating package list and installing prerequisites..."
sudo apt update
sudo apt install -y git autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

# Variables for toolchain
REPO_PATH="$HOME/riscv-gnu-toolchain"
INSTALL_DIR="/opt/riscv"
TOOLCHAIN_PATH="$INSTALL_DIR/bin"

# Step 2: Clone the RISC-V GNU Toolchain Repository
echo "Cloning the RISC-V GNU Toolchain repository..."
if [ ! -d "$REPO_PATH" ]; then
    git clone https://github.com/riscv/riscv-gnu-toolchain "$REPO_PATH"
else
    echo "RISC-V GNU Toolchain repository already exists."
fi

# Step 3: Build and Install the RISC-V Toolchain
echo "Building and installing the RISC-V toolchain..."
cd "$REPO_PATH"
./configure --prefix="$INSTALL_DIR"
make -j$(nproc)

# Step 4: Add the RISC-V toolchain to the PATH
if ! grep -q "$TOOLCHAIN_PATH" ~/.bashrc; then
    echo "Adding RISC-V toolchain to PATH..."
    echo "export PATH=\"$TOOLCHAIN_PATH:\$PATH\"" >> ~/.bashrc
    source ~/.bashrc
else
    echo "RISC-V toolchain is already in PATH."
fi

# Step 5: Verify the Installation
echo "Verifying RISC-V toolchain installation..."
riscv64-unknown-elf-gcc --version || { echo "GCC installation failed"; exit 1; }
riscv64-unknown-elf-as --version || { echo "Assembler installation failed"; exit 1; }

# Optional: Install QEMU for RISC-V emulation
read -p "Do you want to install QEMU for RISC-V emulation? (y/n): " choice
if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
    echo "Installing QEMU..."
    sudo apt install -y qemu-system-misc
    echo "QEMU installation complete."
else
    echo "QEMU installation skipped."
fi

echo "RISC-V toolchain setup complete!"
