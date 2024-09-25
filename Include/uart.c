#include "/Users/deveshshevde/RISC-V/Include/systemaddr.h"

void UART_SEND(const char *str){
    while (*str) {
        *(volatile char*)UART_TX_ADDR = *str++;
    }
}
