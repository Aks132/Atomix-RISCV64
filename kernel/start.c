/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"


int x = 69;
int *y = &x;
int main(){

    UART_SEND(string);
    UART_SEND(fun);
    PrintDigit(x);


    return 0;
}
