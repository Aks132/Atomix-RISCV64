#include "header.h"

volatile static int started = 0;
mutex_t my_mutex;

void system_init(void) {
    mutex_init(&my_mutex, "init mutex");
    uart_init();  // Initialize UART and its mutex
    misa_print();

    
    
}
void misa_print(void){
        unsigned long misa = misa_read();
        unsigned long base_isa = misa & 0x3; 

        switch(base_isa) {
            case 0: my_printf("Base ISA: RV32\n"); break;
            case 1: my_printf("Base ISA: RV64\n"); break;
            case 2: my_printf("Base ISA: RV128\n"); break;
            default: my_printf("Unknown base ISA\n"); break;
        }// finally some use of switch case LOL
    

        my_printf("Supported Extensions:\n");

        if (misa & (1UL << ('I' - 'A'))) my_printf("  Extension: 'I' (Integer)\n");
        if (misa & (1UL << ('M' - 'A'))) my_printf("  Extension: 'M' (Multiply/Divide)\n");
        if (misa & (1UL << ('A' - 'A'))) my_printf("  Extension: 'A' (Atomic)\n");
        if (misa & (1UL << ('F' - 'A'))) my_printf("  Extension: 'F' (Single-Precision Floating Point)\n");
        if (misa & (1UL << ('D' - 'A'))) my_printf("  Extension: 'D' (Double-Precision Floating Point)\n");
        if (misa & (1UL << ('C' - 'A'))) my_printf("  Extension: 'C' (Compressed Instructions)\n");
        if (misa & (1UL << ('S' - 'A'))) my_printf("  Extension: 'S' (Supervisor Mode)\n");
        if (misa & (1UL << ('U' - 'A'))) my_printf("  Extension: 'U' (User Mode)\n");
        if (misa & (1UL << ('Q' - 'A'))) my_printf("  Extension: 'Q' (Quad-Precision Floating Point)\n");
        if (misa & (1UL << ('V' - 'A'))) my_printf("  Extension: 'V' (Vector Operations)\n");
        if (misa & (1UL << ('B' - 'A'))) my_printf("  Extension: 'B' (Bit Manipulation)\n");
        if (misa & (1UL << ('P' - 'A'))) my_printf("  Extension: 'P' (Packed-SIMD)\n");
        if (misa & (1UL << ('H' - 'A'))) my_printf("  Extension: 'H' (Hypervisor)\n");
        if (misa & (1UL << ('E' - 'A'))) my_printf("  Extension: 'E' (Embedded Base Integer ISA)\n");
        if (misa & (1UL << ('J' - 'A'))) my_printf("  Extension: 'J' (Dynamic Translations)\n");
        if (misa & (1UL << ('T' - 'A'))) my_printf("  Extension: 'T' (Transaction Memory)\n");
        if (misa & (1UL << ('L' - 'A'))) my_printf("  Extension: 'L' (Decimal Floating Point)\n");
        if (misa & (1UL << ('N' - 'A'))) my_printf("  Extension: 'N' (User-level interrupts)\n");
        if (misa & (1UL << ('X' - 'A'))) my_printf("  Extension: 'X' (Non-standard extensions)\n");
        if (misa & (1UL << ('Z' - 'A'))) my_printf("  Extension: 'Z' (Standard extensions)\n");
    
    
    unsigned long mstatus = mstatus_read();  // Read the mstatus register
    unsigned long current_privilege = ((mstatus >> 11) & 0x3);  // Extract the current privilege mode

    if (current_privilege == 0x1) {
        my_printf("We are in Supervisor mode!\n");
    } else if (current_privilege == 0x3) {
        my_printf("We are still in Machine mode - > some thing went. wrong pls reset \n");
    } else if (current_privilege == 0x0) {
        my_printf("We are in User mode , something went wrong\n");
    } 

}
int
cpuid()
{
  int id = tp_read();
  return id;
}


void main()
{   
system_init();

       
if (cpuid() == 0){
    my_printf("cpuid %d starting\n", cpuid());
    
    mutex_lock(&my_mutex);
    for(int i=0;i<100;i++){
        my_printf("The number is %d \n",i);
    }
    mutex_unlock(&my_mutex);
    
    kernel_mem_init();
    lib_puts("For now mem alloc is on break\n");

    my_printf("I am printF \n");

    lib_puts("startted\n");

    maketable();

    poweroff();
    // reboot();
    started = 1;
    }
    else{
       while(started == 0);
    __sync_synchronize();
    my_printf("hart %d starting\n", cpuid());

    }
}