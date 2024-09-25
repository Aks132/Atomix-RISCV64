/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/

#define      UART_TX_ADDR      0x10000000UL

int main(){ 
    char *str = "Hello, World!\n";
    for (int i = 0; str[i] != '\0'; ++i) {
        *(volatile char*)UART_TX_ADDR = str[i];
    }
    return 0;
}
