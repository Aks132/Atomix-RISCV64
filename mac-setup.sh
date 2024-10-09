
#!/bin/bash

# RISC-V GNU Toolchain Installation Script for macOS

# Step 1: Install Homebrew (if not installed)
if ! command -v brew &> /dev/null
then
    echo "Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    echo "Homebrew is already installed."
fi

# Step 2: Update Homebrew
echo "Updating Homebrew..."
brew update

# Step 3: Tap the RISC-V repository and install the RISC-V toolchain
echo "Tapping RISC-V repository and installing RISC-V toolchain..."
brew tap riscv/riscv
brew install riscv-gnu-toolchain

# Step 4: Add the RISC-V toolchain to the PATH
TOOLCHAIN_PATH="/usr/local/Cellar/riscv-gnu-toolchain/main/bin"

if ! grep -q "$TOOLCHAIN_PATH" ~/.zshrc; then
    echo "Adding RISC-V toolchain to PATH..."
    echo "export PATH="$TOOLCHAIN_PATH:\$PATH"" >> ~/.zshrc
    source ~/.zshrc
else
    echo "RISC-V toolchain is already in PATH."
fi

# Step 5: Verify the Installation
echo "Verifying RISC-V toolchain installation..."
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-as --version

# Optional: Install QEMU for emulation
read -p "Do you want to install QEMU for RISC-V emulation? (y/n): " choice
if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
    echo "Installing QEMU..."
    brew install qemu
    echo "QEMU installation complete."
else
    echo "QEMU installation skipped."
fi

echo "RISC-V toolchain setup complete!"