#include "header.h"


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


    // unsigned long readSATP = satp_read();
    // PrintDigit(readSATP);
    // satp_write(1<<3);
    // readSATP = satp_read();
    // PrintDigit(readSATP);
    kernel_mem_init();
    lib_puts("For now mem alloc is on break\n");


    my_printf("I am printF \n");

    lib_puts("startted");




    // reboot();

}