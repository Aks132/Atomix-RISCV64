#include "Wprintf.h"
#include "bool.h"
#include "stdarg.h"

mutex_t uart_mutex;

status_t PrintChar(const char x) {
    char temp[2] = {x, '\0'};
    UART_SEND(temp);
    return SUCCESS;
}

status_t PrintDigit(const unsigned long number) {
    char str[100];
    UART_SEND(itoa(number, str, 10));
    return SUCCESS;
}

status_t PrintHex(const int number) {
    char str[100];
    UART_SEND(itoa(number, str, 16));
    return SUCCESS;
}

void Println() {
    *(volatile char*)UART_TX_ADDR = '\n';
}

void reverse(char str[], int length) {
    int start, end = length - 1;
    for (start = 0; start < end; ++start, --end) {
        const char ch = str[start];
        str[start] = str[end];
        str[end] = ch;
    }
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    char isNegNum = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
    } else {
        if ((num < 0) && (base == 10)) {
            isNegNum = 1;
            num = -num;
        }
        do {
            const int rem = (num % base);
            str[i++] = (rem > 9) ? ((rem - 10) + 'a') : (rem + '0');
            num = num / base;
        } while (num != 0);
        if (isNegNum) {
            str[i++] = '-';
        }
        str[i] = '\0';
        reverse(str, i);
    }
    return str;
}

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    mutex_lock(&uart_mutex,&threads[mhartid()]);

    while (*format) {
        if (*format == '%') {
            format++; // Move past the '%' character
            switch (*format) {
                case 'c': { // Character
                    char ch = (char)va_arg(args, int);
                    lib_putc(ch); // Use lib_putc
                    break;
                }
                case 'd': { // Decimal (unsigned long)
                    unsigned long num = va_arg(args, unsigned long);
                    PrintDigit(num);
                    break;
                }
                case 'x': { // Hexadecimal
                    int num = va_arg(args, int);
                    PrintHex(num);
                    break;
                }
                case 's': { // String
                    const char *str = va_arg(args, const char *);
                    UART_SEND(str); // Keep UART_SEND for sending strings
                    break;
                }
                case 'p': { // Pointer
                    void* ptr = va_arg(args, void*);
                    lib_putc('0'); // Print '0' for the start of the hex
                    lib_putc('x'); // Print 'x' to indicate hex
                    PrintHex((unsigned long)ptr); // Print the pointer in hex
                    break;
                }
                case 'u': { // Unsigned decimal
                    unsigned int num = va_arg(args, unsigned int);
                    PrintDigit(num);
                    break;
                }
                case 'l': { // Long long
                    format++; // Move to next character (should be 'u' or 'd')
                    if (*format == 'u') { // Handle %llu
                        unsigned long long num = va_arg(args, unsigned long long);
                        PrintDigit(num); // Print unsigned long long
                    } else if (*format == 'd') { // Handle %lld
                        long long num = va_arg(args, long long);
                        PrintDigit(num); // Print signed long long
                    } else { // Handle unsupported specifier
                        lib_putc('%'); // Print the '%' sign
                        lib_putc('l'); // Print 'l' for clarity
                        lib_putc(*format); // Print the format specifier
                    }
                    break;
                }
                default: // Unknown format specifier
                    lib_putc('%'); // Print the '%' sign
                    lib_putc(*format); // Print the format specifier
                    break;
            }
        } else {
            // Print regular characters
            lib_putc(*format); // Use lib_putc to print characters
        }
        format++;
    }
    
    mutex_unlock(&uart_mutex,&threads[mhartid()]);
    va_end(args);
}
