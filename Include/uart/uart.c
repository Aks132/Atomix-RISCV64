#include "uart.h"

#define UART        0x10000000
#define UART_THR    (volatile unsigned char*)(UART + 0x00) 
#define UART_LSR    (volatile unsigned char*)(UART + 0x05) 
#define UART_LSR_EMPTY_MASK 0x40    
#define UART_LSR_READY_MASK 0x01 


void lib_putc(char ch) {
    while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
    *UART_THR = ch;
}

char lib_getc() {
    while ((*UART_LSR & UART_LSR_READY_MASK) == 0); 
    return *(volatile char *)(UART + 0x00); 
}

void lib_puts(const char *s) {
    while (*s) {
        lib_putc(*s++);
    }
}
void UART_SEND(const char *str) {
    
    while (*str) {
        while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
        *UART_THR = *str++;
    }
}


