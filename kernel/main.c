#include "header.h"

    volatile unsigned char* io_base = (volatile unsigned char*) 0x40000000; // Replace 0xADDRESS with actual I/O base address
#define FB_BASE 0x50000000  // Framebuffer base address

int main()
{
    unsigned long mstatus = mstatus_read();  // Read the mstatus register
    unsigned long current_privilege = ((mstatus >> 11) & 0x3);  // Extract the current privilege mode

    if (current_privilege == 0x1) {
        my_printf("We are in Supervisor mode!\n");
    } else if (current_privilege == 0x3) {
        my_printf("We are still in Machine mode - > some thing went. wrong pls reset \n");
    } else if (current_privilege == 0x0) {
        my_printf("We are in User mode , something went wrong\n");
    } 



    kernel_mem_init();
    lib_puts("For now mem alloc is on break\n");


    lib_puts("startted");



    my_printf("I am printF \n");

    lib_puts("startted\n");

    maketable();
    
    enumerate_pci_devices();
    set_mode13();

        
 
    return 0;
    

    // poweroff();
    // reboot();

}