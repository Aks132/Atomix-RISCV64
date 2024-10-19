#include "uart/uart.h"  // Include UART for printing debug information
#include "mtime.h"
#include "scheduler/scheduler.h"
#include "mutex/mutex.h"


#define MTIME_BASE 0x0200BFF8  // Base address for mtime
#define MTIMECMP_BASE 0x02004000  // Base address for mtimecmp
#define CLOCK_FREQUENCY 1000000  // Adjust to match your clock frequency (e.g., 10 MHz)

mutex_t delay_mutex;

// Initialize the timer
void timer_init(void) {
    mutex_init(&delay_mutex,"delay mutex");
    // Set mtimecmp to a future time to avoid immediate interrupts
    *((volatile uint64_t *)MTIMECMP_BASE) = timer_get_time() + CLOCK_FREQUENCY;

    // Set up your interrupt controller for handling timer interrupts (if needed)
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
    uint64_t new_cmp = current_time + (delay_us * CLOCK_FREQUENCY / 1000000);  // Adjust delay_us based on clock frequency

    // Set the mtimecmp register to trigger the next timer interrupt
    *((volatile uint64_t *)MTIMECMP_BASE) = new_cmp;
}

// Function for non-blocking delay
void non_blocking_delay(uint64_t delay_us) {
   // mutex_lock(&delay_mutex);
    timer_set(delay_us);  // Set the timer

    while (1) {
        // Check if the timer has expired
        if (timer_get_time() >= *((volatile uint64_t *)MTIMECMP_BASE)) {
            break;  // Delay is over
        }
        // Optional: Yield CPU time to other tasks here if multitasking is enabled
    }
   // mutex_unlock(&delay_mutex);

}
// Timer interrupt handler
void timer_handler(void) {
    // Acknowledge the timer interrupt by setting the next timer interval
    uint64_t current_time = timer_get_time();
    *((volatile uint64_t *)MTIMECMP_BASE) = current_time + CLOCK_FREQUENCY;  // Set the next comparison time

    UART_SEND("Timer interrupt occurred\n");
    
    schedule();
}
