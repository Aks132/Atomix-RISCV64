#include "../Include/libc/Wprintf.h"
#include "../Include/libc/bool.h"

status_t PrintChar(char * x){
      UART_SEND(x);
      return SUCCESS;
}
status_t PrintDigit(const int number){
  char str[100];
  UART_SEND(itoa(number, str, 10));
}
status_t PrintHex(const int number){
    char str[100];
    UART_SEND(itoa(number, str, 16));
}

void reverse(char str[], int length)
{
    int start;
    int end = length -1;
    for(start = 0; start < end; ++start, --end)
    {
        const char ch = str[start];
        str[start] = str[end];
        str[end] = ch;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    char isNegNum = 0;
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
    }
    else
    {
        if ((num < 0) && (base == 10))
        {
            isNegNum = 1;
            num = -num;
        }
        do
        {
            const int rem = (num % base);
            str[i++] = (rem > 9)? ((rem-10) + 'a') : (rem + '0');
            num = num/base;
        }
        while (num != 0);
        if (isNegNum)
        {
            str[i++] = '-';
        }
        str[i] = '\0';
        reverse(str, i);
    }
    return str;
}
