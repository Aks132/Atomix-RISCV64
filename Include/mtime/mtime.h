#ifndef MTIME_H
#define MTIME_H

#include "libc/types.h"

// Function to initialize the timer
void timer_init(void);

// Function to get the current time from the timer (in microseconds)
uint64_t timer_get_time(void);

// Function to set the timer for a specified delay (in microseconds)
void timer_set(uint64_t delay_us);

// Function for non-blocking delay
void non_blocking_delay(uint64_t delay_us);

// Timer interrupt handler
void timer_handler(void);

<<<<<<< HEAD
#endif // MTIME_H
=======
#endif // MTIME_H
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
