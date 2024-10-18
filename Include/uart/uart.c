<<<<<<< HEAD
#include "uart.h"
=======
#include "uart/uart.h"
#include "mutex/mutex.h"
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241

#define UART        0x10000000
#define UART_THR    (volatile unsigned char*)(UART + 0x00) // THR: Transmitter holding register
#define UART_LSR    (volatile unsigned char*)(UART + 0x05) // LSR: Line status register
#define UART_LSR_EMPTY_MASK 0x40                     // LSR Bit 6: Transmitter empty; both THR and LSR are empty


void uart_init(void){
    //need to add some things later.

}
void lib_putc(char ch) {
    while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
    *UART_THR = ch;
    return;
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


