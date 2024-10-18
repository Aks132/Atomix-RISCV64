<<<<<<< HEAD
#pragma once
#include "stdarg.h"
#include "status.h"
#include "uart/uart.h"
=======
#ifndef __WPRINTF_H__
#define __WPRINTF_H__

#include "libc/stdarg.h"
#include "status.h"
#include "uart/uart.h"
#include "mutex/mutex.h"

extern mutex_t uart_mutex;
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241

status_t PrintChar(const char  x);
status_t PrintDigit(const unsigned long number);
char* itoa(int num, char* str, int base);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
void Println();
void my_printf(const char *format, ...);

