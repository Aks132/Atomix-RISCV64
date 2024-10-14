#ifndef WPRINTF
#define WPRINTF

#include "libc/stdarg.h"
#include "status.h"
#include "uart/uart.h"
#include "mutex/mutex.h"
#include "mutex/threads.h"

extern mutex_t uart_mutex;

status_t PrintChar(const char  x);
status_t PrintDigit(const unsigned long number);
char* itoa(int num, char* str, int base);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
void Println();
void my_printf(const char *format, ...);

#endif