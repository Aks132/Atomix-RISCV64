#include "../Include/systemaddr.h"

#define UART        0x10000000
#define UART_THR    (volatile unsigned char*)(UART + 0x00) // THR: Transmitter holding register
#define UART_LSR    (volatile unsigned char*)(UART + 0x05) // LSR: Line status register
#define UART_LSR_EMPTY_MASK 0x40                     // LSR Bit 6: Transmitter empty; both THR and LSR are empty

// Function to send a single character when UART is ready
int lib_putc(char ch) {
    // Wait until the transmitter holding register is empty
    while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
    *UART_THR = ch;
    return 0;
}

// Function to send a string via UART
void lib_puts(const char *s) {
    while (*s) {
        lib_putc(*s++);
    }
}

// Optimized function to send a string via UART without checking each character
void UART_SEND(const char *str) {
    while (*str) {
        // Wait until the UART transmitter is ready to send
        while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
        *UART_THR = *str++;
    }
}


