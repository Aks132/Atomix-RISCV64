#include "../Include/uart/uart.h"
#include "../include/mutex/mutex.h"

// Mutex for UART access
mutex_t uart_mutex;

// Semaphore for controlling access to UART
semaphore_t uart_semaphore;

void uart_init() {
    // Initialize the UART mutex
    mutex_init(&uart_mutex, "UART");

    // Initialize the UART semaphore with an initial value of 1 (binary semaphore)
    sem_init(&uart_semaphore, 1);
}

// Function to send a single character via UART
void lib_putc(char ch) {
    sem_wait(&uart_semaphore);  // Wait on the semaphore to access UART
    mutex_lock(&uart_mutex);    // Lock the mutex for UART access

    while (!uart_tx_ready());   // Wait until UART transmitter is ready
    *UART_REG(UART_THR_OFFSET) = ch;  // Write the character to the Transmitter Holding Register

    mutex_unlock(&uart_mutex);  // Unlock the mutex
    sem_signal(&uart_semaphore);  // Signal the semaphore to release UART access
}

// Function to send a string via UART
void lib_puts(const char *s) {
    while (*s) {
        lib_putc(*s++);  // Send each character
    }
}

// Function to send a string via UART, optimized without checking each character
void UART_SEND(const char *str) {
    sem_wait(&uart_semaphore);  // Wait on the semaphore to access UART
    mutex_lock(&uart_mutex);    // Lock the mutex for UART access

    while (*str) {
        while (!uart_tx_ready());  // Wait until UART transmitter is ready
        *UART_REG(UART_THR_OFFSET) = *str++;  // Write the character to the Transmitter Holding Register
    }

    mutex_unlock(&uart_mutex);  // Unlock the mutex
    sem_signal(&uart_semaphore);  // Signal the semaphore to release UART access
}
