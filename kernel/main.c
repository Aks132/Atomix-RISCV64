#include "header.h"

void kinit() {
    unsigned long misa = misa_read();
    unsigned long base_isa = misa & 0x3; 

    switch(base_isa) {
        case 0: my_printf("Base ISA: RV32\n"); break;
        case 1: my_printf("Base ISA: RV64\n"); break;
        case 2: my_printf("Base ISA: RV128\n"); break;
        default: my_printf("Unknown base ISA\n"); break;
    }

    my_printf("Supported Extensions:\n");

    if (misa & (1UL << ('I' - 'A'))) my_printf("  Extension: 'I' (Integer)\n");
    if (misa & (1UL << ('M' - 'A'))) my_printf("  Extension: 'M' (Multiply/Divide)\n");
    if (misa & (1UL << ('A' - 'A'))) my_printf("  Extension: 'A' (Atomic)\n");
    if (misa & (1UL << ('F' - 'A'))) my_printf("  Extension: 'F' (Single-Precision Floating Point)\n");
    if (misa & (1UL << ('D' - 'A'))) my_printf("  Extension: 'D' (Double-Precision Floating Point)\n");
    if (misa & (1UL << ('C' - 'A'))) my_printf("  Extension: 'C' (Compressed Instructions)\n");
    if (misa & (1UL << ('S' - 'A'))) my_printf("  Extension: 'S' (Supervisor Mode)\n");
    if (misa & (1UL << ('U' - 'A'))) my_printf("  Extension: 'U' (User Mode)\n");
    
    unsigned long mstatus = mstatus_read();  
    unsigned long current_privilege = ((mstatus >> 11) & 0x3); 

    if (current_privilege == 0x1) {
        my_printf("We are in Supervisor mode!\n");
    } else if (current_privilege == 0x3) {
        my_printf("We are in Machine mode, something went wrong!\n");
    } else if (current_privilege == 0x0) {
        my_printf("We are in User mode, something went wrong!\n");
    } 
    
    kernel_mem_init();
    maketable();

}

void kinit_hart(){


}
void make_syscall();

void main() {

    my_printf("I am into main....\n");
    // if (mhartid() == 0) {
        
 

    

    //     enumerate_pci_devices();
    //     set_mode13();
    //     //make_syscall();   
    // }
}
