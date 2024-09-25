/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/systemaddr.h"
#include "../Include/sysprints.h"
void UART_SEND(const char *str){
    while (*str) {
        *(volatile char*)UART_TX_ADDR = *str++;
    }
}


int main(){ 
    
    UART_SEND(string);
    UART_SEND(fun);

    return 0;
}
