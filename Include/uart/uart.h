#ifndef UART_H
#define UART_H
#include "../Include/mutex/mutex.h"

#define      UART_TX_ADDR      0x10000000UL
int lib_putc(char ch);
void lib_puts(const char *s);
void UART_SEND(const char *str);

#endif
//00010000
//00000000
//00000000
//00000000