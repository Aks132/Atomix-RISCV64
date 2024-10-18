<<<<<<< HEAD
#ifndef UART_H
#define UART_H
#include "mutex/mutex.h"

// #define      UART_TX_ADDR      0x10000000UL
 #define      UART_TX_ADDR       0x30000000
int lib_putc(char ch);
=======
#ifndef __UART_H__
#define __UART_H__

#define UART_BASE_ADDR 0x10000000UL
#define UART_TX_ADDR   0x10000000UL

#define UART_THR_OFFSET 0x00 // Transmitter Holding Register
#define UART_LSR_OFFSET 0x05 // Line Status Register
#define UART_LSR_TX_EMPTY (1 << 5) // Line Status Register TX empty flag

void uart_init(void);
void lib_putc(char ch);
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
void lib_puts(const char *s);
void UART_SEND(const char *str);
void UART_DEBUG(const char *str);

#endif // __UART_H__
