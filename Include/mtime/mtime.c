#include "uart/uart.h" // Include UART for printing debug information
#include "mtime.h"

#define MTIME_BASE 0x0200BFF8 // Adjust the base address for mtime
#define MTIMECMP_BASE 0x02004000 // Adjust the base address for mtimecmp

// Initialize the timer
void timer_init(void) {
    // Clear mtimecmp initially
    *((volatile uint64_t *)MTIMECMP_BASE) = 0;

    // Here, you may want to set up your interrupt controller for handling timer interrupts.
}

// Get the current time in microseconds
uint64_t timer_get_time(void) {
    return *((volatile uint64_t *)MTIME_BASE);
}

// Set the timer for a specified delay (in microseconds)
void timer_set(uint64_t delay_us) {
    // Get the current time
    uint64_t current_time = timer_get_time();
    
    // Calculate the new mtimecmp value
    uint64_t new_cmp = current_time + delay_us; // Adjust this calculation based on your clock frequency

    // Set the mtimecmp register
    *((volatile uint64_t *)MTIMECMP_BASE) = new_cmp;
}

// Timer interrupt handler
void timer_handler(void) {
    // Acknowledge the timer interrupt (clear the interrupt)
    // You might write to an interrupt controller or do specific handling here
    UART_SEND("Timer interrupt occurred\n");
}

// Function for non-blocking delay
void non_blocking_delay(uint64_t delay_us) {
    timer_set(delay_us); // Set the timer

    while (1) {
        // Check if the timer has expired
        if (timer_get_time() >= *((volatile uint64_t *)MTIMECMP_BASE)) {
            break; // Delay is over
        }
        // You can perform other tasks or sleep to save CPU cycles here
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
