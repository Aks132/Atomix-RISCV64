#ifndef UART_H
#define UART_H

// UART register base address
#define UART_BASE_ADDR 0x10000000UL
#define UART_TX_ADDR   0x10000000UL

// Register offsets
#define UART_THR_OFFSET 0x00 // Transmitter Holding Register
#define UART_LSR_OFFSET 0x05 // Line Status Register
#define UART_LSR_TX_EMPTY (1 << 5) // Line Status Register TX empty flag

// Function prototypes
void uart_init(void);
void lib_putc(char ch);
void lib_puts(const char *s);
void UART_SEND(const char *str);

// Inline function to read UART register
static inline volatile unsigned char *UART_REG(unsigned long offset) {
    return (volatile unsigned char *)(UART_BASE_ADDR + offset);
}

// Inline function to check if UART transmitter is ready
static inline int uart_tx_ready(void) {
    return (*UART_REG(UART_LSR_OFFSET) & UART_LSR_TX_EMPTY) != 0;
}

#endif // UART_H
