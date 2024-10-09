// mtime.h - Header file for accessing mtime and creating non-blocking delays
#ifndef MTIME_H
#define MTIME_H

#include "../include/libc/types.h"

#define MTIME_ADDR    0x0200BFF8   // Base address of the mtime register
#define TIMER_FREQ    1000000      // Assuming 1 tick = 1 microsecond, adjust this based on your system

// Function to read the current value of the mtime register
uint64_t read_mtime(void);

// Non-blocking delay function that delays for the specified time in microseconds
void non_blocking_delay(uint64_t delay_in_microseconds);

#endif  // MTIME_H
