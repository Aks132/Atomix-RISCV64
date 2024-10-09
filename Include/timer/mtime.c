// mtime.c - Implementation file for reading mtime and non-blocking delay
#include "mtime.h"

// Read the current value of the mtime register (64-bit)
uint64_t read_mtime(void) {
    return *((volatile uint64_t *)MTIME_ADDR);
}

// Non-blocking delay function
void non_blocking_delay(uint64_t delay_in_microseconds) {
    uint64_t start_time = read_mtime();  // Get the current system time
    uint64_t target_time = start_time + delay_in_microseconds;

    // Loop until the current time reaches the target time
    while (read_mtime() < target_time) {
        // Non-blocking code can be executed here
    }
}
