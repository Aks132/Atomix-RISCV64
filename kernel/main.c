#include "header.h"

mutex_t uart_mutex;

void sys_init() {
    // Initialize system, UART mutex, and print ISA information
    mutex_init(&uart_mutex, "uart Mutex");

    unsigned long misa = misa_read();
    unsigned long base_isa = misa & 0x3; 

    switch(base_isa) {
        case 0: my_printf("Base ISA: RV32\n"); break;
        case 1: my_printf("Base ISA: RV64\n"); break;
        case 2: my_printf("Base ISA: RV128\n"); break;
        default: my_printf("Unknown base ISA\n"); break;
    }

    my_printf("Supported Extensions:\n");
    mutex_lock(&uart_mutex);
    if (misa & (1UL << ('I' - 'A'))) my_printf("  Extension: 'I' (Integer)\n");
    if (misa & (1UL << ('M' - 'A'))) my_printf("  Extension: 'M' (Multiply/Divide)\n");
    if (misa & (1UL << ('A' - 'A'))) my_printf("  Extension: 'A' (Atomic)\n");
    if (misa & (1UL << ('F' - 'A'))) my_printf("  Extension: 'F' (Single-Precision Floating Point)\n");
    if (misa & (1UL << ('D' - 'A'))) my_printf("  Extension: 'D' (Double-Precision Floating Point)\n");
    if (misa & (1UL << ('C' - 'A'))) my_printf("  Extension: 'C' (Compressed Instructions)\n");
    if (misa & (1UL << ('S' - 'A'))) my_printf("  Extension: 'S' (Supervisor Mode)\n");
    if (misa & (1UL << ('U' - 'A'))) my_printf("  Extension: 'U' (User Mode)\n");
    mutex_unlock(&uart_mutex);

    unsigned long mstatus = mstatus_read();  
    unsigned long current_privilege = ((mstatus >> 11) & 0x3);  
    mutex_lock(&uart_mutex);
    if (current_privilege == 0x1) {
        my_printf("We are in Supervisor mode!\n");
    } else if (current_privilege == 0x3) {
        my_printf("We are in Machine mode, something went wrong!\n");
    } else if (current_privilege == 0x0) {
        my_printf("We are in User mode, something went wrong!\n");
    } 
    mutex_unlock(&uart_mutex);
}

void task1() {
    while (1) {
        mutex_lock(&uart_mutex);
        my_printf("Task 1 is running on core %d\n", (int)mhartid());
        mutex_unlock(&uart_mutex);

        for (volatile int i = 0; i < 1000000; i++);  // Simulate work
    }
}

void task2() {
    while (1) {
        mutex_lock(&uart_mutex);
        my_printf("Task 2 is running on core %d\n", (int)mhartid());
        for (volatile int i = 0; i < 1000000; i++);  // Simulate work
        mutex_unlock(&uart_mutex);

    }
}

void task3() {
    while (1) {
        mutex_lock(&uart_mutex);
        my_printf("Task 3 is running on core %d\n", (int)mhartid());
        for (volatile int i = 0; i < 1000000; i++);  // Simulate work
        mutex_unlock(&uart_mutex);

    }
}

int main() {
    sys_init();  // Initialize the system (this can be done by any core)

    // Assign tasks based on the core (hart ID)
    if (mhartid() == 0) {
        task1();  // Core 0 runs Task 1
    } else if (mhartid() == 1) {
        task2();  // Core 1 runs Task 2
    } else if (mhartid() == 2) {
        task3();  // Core 2 runs Task 3
    } else {
        // Other cores can run idle tasks or other work
        my_printf("Core %d is idle\n",(int)mhartid());
        while (1);
    }

    return 0;
}
