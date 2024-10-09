#include "../Include/libc/Wprintf.h"
#include "../Include/libc/bool.h"
#include "../Include/libc/stdarg.h"

// status_t PrintChar(const char * x){
//       UART_SEND(x);
//       return SUCCESS;
// }
// status_t PrintDigit(const unsigned long number){
//   char str[100];
//   UART_SEND(itoa(number, str, 10));
//   return SUCCESS;
// }
// status_t PrintHex(const int number){
//     char str[100];
//     UART_SEND(itoa(number, str, 16));
// }
// void Println(){
//     *(volatile char*)UART_TX_ADDR = '\n';

// }

// void reverse(char str[], int length)
// {
//     int start;
//     int end = length -1;
//     for(start = 0; start < end; ++start, --end)
//     {
//         const char ch = str[start];
//         str[start] = str[end];
//         str[end] = ch;
//     }
// }

// char* itoa(int num, char* str, int base)
// {
//     int i = 0;
//     char isNegNum = 0;
//     if (num == 0)
//     {
//         str[i++] = '0';
//         str[i] = '\0';
//     }
//     else
//     {
//         if ((num < 0) && (base == 10))
//         {
//             isNegNum = 1;
//             num = -num;
//         }
//         do
//         {
//             const int rem = (num % base);
//             str[i++] = (rem > 9)? ((rem-10) + 'a') : (rem + '0');
//             num = num/base;
//         }
//         while (num != 0);
//         if (isNegNum)
//         {
//             str[i++] = '-';
//         }
//         str[i] = '\0';
//         reverse(str, i);
//     }
//     return str;
// }


// void my_printf(const char *format, ...) {
//     va_list args;
//     va_start(args, format);

//     while (*format) {
//         if (*format == '%') {
//             format++; // Move past the '%' character
//             switch (*format) {
//                 case 'c': { // Character
//                     char ch = (char)va_arg(args, int);
//                     PrintChar(&ch);
//                     break;
//                 }
//                 case 'd': { // Decimal
//                     unsigned long num = va_arg(args, unsigned long);
//                     PrintDigit(num);
//                     break;
//                 }
//                 case 'x': { // Hexadecimal
//                     int num = va_arg(args, int);
//                     PrintHex(num);
//                     break;
//                 }
//                 case 's': { // String
//                     const char *str = va_arg(args, const char *);
//                     PrintChar(str);
//                     break;
//                 }
//                 default:
//                     break;
//             }
//         } else {
//             // Print regular characters
//             PrintChar(format);
//         }
//         format++;
//     }
//     va_end(args);
// }



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

// Custom printf function
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++; // Move past the '%' character
            switch (*format) {
                case 'c': { // Character
                    char ch = (char)va_arg(args, int);
                    PrintChar(ch);
                    break;
                }
                case 'd': { // Decimal
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
                    UART_SEND(str);
                    break;
                }
                case 'p': { // Pointer
                    void* ptr = va_arg(args, void*);
                    PrintChar('0'); // Print '0' for the start of the hex
                    PrintChar('x'); // Print 'x' to indicate hex
                    PrintHex((unsigned long)ptr); // Print the pointer in hex
                    break;
                }
                default: // Unknown format specifier, ignore it
                    PrintChar('%'); // Print the '%' sign
                    PrintChar(*format); // Print the format specifier
                    break;
            }
        } else {
            // Print regular characters
            PrintChar(*format);
        }
        format++;
    }
    va_end(args);
}
