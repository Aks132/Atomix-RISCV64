#ifndef WPRINTF
#define WPRINTF

#include "../Include/libc/stdarg.h"
#include "../Include/status.h"
#include "../Include/uart/uart.h"

status_t PrintChar(const char  x);
status_t PrintDigit(const unsigned long number);
char* itoa(int num, char* str, int base);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
void Println();
void my_printf(const char *format, ...);

#endif