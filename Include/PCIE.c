#include "PCIE.h"

// https://wiki.osdev.org/PCI

typedef struct {
    uint16_t vendor_id;
    uint16_t device_id;
    void (*setup_function)(); 
} pci_device_t;


//https://www.qemu.org/docs/master/specs/pci-ids.html
pci_device_t pci_registry[] = {
    { 0x1B36, 0x0008, setup_qemu_pci_bridge },
    {0x1AF4,0x1050,setup_pci_vga},                  
    { 0xFFFF, 0xFFFF, NULL },
};

uint32_t pci_read(uint32_t offset) {
    return *((volatile uint32_t *)((uintptr_t)(PCI_BASE_ADDR + offset)));
}
void enumerate_pci_devices() {
    uint32_t offset = 0;
    uint32_t device_header;
    uint16_t vendor_id, device_id;
    
    my_printf("Vendor ID\tDevice ID\n");
  

    while (offset < 0x10000000) { 
        device_header = pci_read(offset);  
        vendor_id = device_header & 0xFFFF; 
        device_id = (device_header >> 16) & 0xFFFF; 
        if (vendor_id == 0xFFFF) {
            offset += 0x100;
            continue;
        }
        my_printf("%x     and     %x \n", vendor_id, device_id);
        for (int i = 0; pci_registry[i].vendor_id != 0xFFFF; i++) {
            if (pci_registry[i].vendor_id == vendor_id && pci_registry[i].device_id == device_id) {
                    if (pci_registry[i].setup_function) {
                    // my_printf("%d number of calls \n",++count);
                    // my_printf("Calling setup function for vendor ID %x, device ID %x\n", vendor_id, device_id);
                    pci_registry[i].setup_function();
                }
            }
        }
        offset += PCI_HEADER_SIZE;
    }
}

void setup_qemu_pci_bridge(){
    my_printf("qemu bridge setup done!! \n");
}

void write_volatile(uint32_t *addr, uint32_t value) {
    *((volatile uint32_t *)addr) = value;
}

uint32_t read_volatile(uint32_t *addr) {
    return *((volatile uint32_t *)addr);
}

void setup_pci_vga() {
    my_printf("Setting PCIE VGA\n");
    
    uint32_t *dev_base = (uint32_t*)0x30008000;
    uint32_t *fb_base = (uint32_t*)0x50000000;
    write_volatile(dev_base + 4, 0xFFFFFFFF);  // dev_base + 4 bytes = dev_base + 1 (32-bit pointers)
    uint32_t fb_size = (~read_volatile(dev_base + 4) | 0xF) + 1;  // dev_base + 1 for 4-byte offset
    // my_printf("FB size: %d\n", fb_size);
    uint32_t *io_base = fb_base + (fb_size / sizeof(uint32_t));  // Divide by sizeof(uint32_t) for correct offset
    // my_printf("IO base val: %p\n", io_base);
    write_volatile(dev_base + 6, 0xFFFFFFFF);  // dev_base + 6 bytes = dev_base + 3 (32-bit pointers)
    uint32_t io_size = (~read_volatile(dev_base + 6) | 0xF) + 1;  // dev_base + 3 for 6-byte offset
    // my_printf("FB base: %p\n", fb_base);
    write_volatile(dev_base + 4, (uint32_t)((uintptr_t)fb_base) | 0x8);  // dev_base + 4 bytes = dev_base + 1
    write_volatile(dev_base + 6, (uint32_t)((uintptr_t)io_base) | 0x8);  // dev_base + 6 bytes = dev_base + 3
    uint32_t *cmd = dev_base;
    write_volatile(cmd + 1, read_volatile(cmd + 1) | 0x0002);  // cmd register at dev_base + 1
    my_printf("VGA fb_base: %p, size: %d MB, io_base: %p, io_size: %x\n",
           fb_base,
           (fb_size + 0x80000) >> 20,  // size in MB
           io_base,
           io_size);
}
