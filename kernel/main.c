#include "header.h"

volatile static int next_hart_to_start = 0;
mutex_t my_mutex;

void thread_function(void *arg) {
    pthread_descr *self = (pthread_descr *)arg;
    int my_hartid = mhartid();  // Get the hart's ID

    // Ensure each hart starts in sequence
    while (next_hart_to_start != my_hartid) {
        // Spin and wait until it's this hart's turn
    }

    // Acquire the mutex before entering the critical section
    mutex_lock(&my_mutex, self);

    // Critical section: print the hart's information
    my_printf("hart %d starting\n", mhartid());

    // Increment to signal the next hart to proceed
    next_hart_to_start++;

    // Release the mutex after the critical section
    mutex_unlock(&my_mutex, self);
}

void system_init(void) {
    uart_init();
    // Initialize the system, UART, and other peripherals here
}

int cpuid() {
    int id = tp_read();
    return id;
}

void main() {
    // Initialize the thread system and system peripherals
    init_thread_system();
    system_init();

    // Initialize the mutex
    mutex_init(&my_mutex);
    
    if (mhartid() == 0) {
        // Hart 0 prints its message and sets up threads for the other harts

        // Print from the main hart (hart 0) first
        mutex_lock(&my_mutex, &threads[0]);
        my_printf("hart %d starting\n", mhartid());
        mutex_unlock(&my_mutex, &threads[0]);

        // Set the next hart to start after hart 0
        next_hart_to_start = 1;

        // Create threads for other harts to execute sequentially
        create_thread(thread_function, &threads[1]);
        create_thread(thread_function, &threads[2]);
        create_thread(thread_function, &threads[3]);

        // Hart 0 does not enter the scheduler again, it just waits
        while (1);  // Hart 0 halts after initialization
    } else {
        // Each hart will start only when it's their turn
        while (next_hart_to_start != mhartid()) {
            // Spin and wait until it's this hart's turn
        }

        // Execute thread function for this hart
        thread_function(&threads[mhartid()]);

        // Prevent harts from executing the function again
        while (1);  // Halt this hart after execution to avoid reprinting
    }
}
