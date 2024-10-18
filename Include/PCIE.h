//riscV/vict.h
#pragma once

<<<<<<< HEAD
#include "Wprintf.h"
=======
#include "libc/Wprintf.h"
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uintptr_t;

//https://wiki.osdev.org/PCI#Enumerating_PCI_Buses

#define NULL 0
#define PCI_BASE_ADDR 0x30000000  // Base address of PCI configuration space
#define PCI_HEADER_SIZE 4096      // Size of each PCI device's configuration space


void enumerate_pci_devices();
void setup_qemu_pci_bridge();
void setup_pci_vga();
// void setup_vga();
// void setup_qemu_vga();

/*
    * sources you can refer !
    * https://www.youtube.com/watch?v=L9qXjmJdQXY&t=346s
    * 
*/