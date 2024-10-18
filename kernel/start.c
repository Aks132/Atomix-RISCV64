#include "start.h"


const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";

unsigned long id;
unsigned long var;
unsigned long getMPP;
unsigned long sieregister;

mutex_t my_mutex;
volatile int cores_ready = 0; // Shared counter to track how many cores are ready

// Total number of cores in the system (4 in this case)
#define NUM_CORES 4

// Boot.S needs one stack per CPU.

void Start() {
    mutex_lock(&my_mutex);
    my_printf("core number : %d \n ", mhartid());
    cores_ready++;  // Increment the counter for ready cores
    mutex_unlock(&my_mutex);
    // mutex_init(&my_mutex, "my mutex");
    var = mstatus_read();
    var &= ~(3UL << 11); // 11 -> machine mode
    var |= (1UL << 11);  // 01 -> supervisor mode
    mstatus_write(var);
    set_mepc((unsigned long)main());

    write_medeleg(0xFFFF);
    write_mideleg(0xFFFF);
    sieregister = sie_read();
    sieregister |= ((1UL << 1) | (1UL << 5) | (1UL << 9)); // Enable 3 ints for S mode
    sie_write(sieregister | ((1UL << 1) | (1UL << 5) | (1UL << 9)));

    pmpaddr0_write(0x3fffffffffffffull);
    pmpcfg0_write(0xf);

    mie_write(mie_read() | (1L << 5)); // Enable supervisor-mode timer interrupts
    menvcfg_write(menvcfg_read() | (1L << 63)); // Enable SSTC extension
    mcounteren_write(mcounteren_read() | 2);    // Allow supervisor to use stimecmp and time

    stimecmp_write(time_read() + 1000000); // Request the very first timer interrupt

    // Wait for all cores to be ready
    while (cores_ready < NUM_CORES) {
        // Busy wait or implement a more efficient wait here
    }

    mret(); // Proceed to supervisor mode and jump to main only when all cores are ready
}

void Core0_Init() {
    Start();
}

void Core1_Init() {
    Start();
}

void Core2_Init() {
    Start();
}

void Core3_Init() {
    Start();
}