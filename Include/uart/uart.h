#ifndef UART_H
#define UART_H
#include "mutex/mutex.h"


 #define      UART_TX_ADDR       0x30000000
void lib_putc(char ch);
void lib_puts(const char *s);
void UART_SEND(const char *str);
char lib_getc();
#endif
