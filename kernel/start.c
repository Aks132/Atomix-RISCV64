/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"

#include "mutex.h"
const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";
mutex_t my_mutex;

void shared_resource() {
    mutex_lock(&my_mutex);
    UART_SEND("Lock acquired, modifying shared resource...\n");
    for (volatile int i = 0; i < 1000000; i++);

    UART_SEND("Releasing lock...\n");

    mutex_unlock(&my_mutex);
}

int start(){
    // mutex_init(&my_mutex);

    UART_SEND("Starting system...\n");

    Println();
    Println();
    PrintDigit(hartid0);
    Println();
    Println();
    PrintDigit(hartid1);
    Println();
    Println();
    PrintDigit(hartid2);
    Println();
    Println();
    PrintDigit(hartid3);
    Println();
    Println();
    PrintChar(AllCoreBootsUp);




}

void Core0_Init(){
    PrintChar(core0);
    PrintDigit(1234);

}


void Core1_Init(){
    PrintChar(core1);
    PrintDigit(1234);

}

void Core2_Init(){
    PrintChar(core2);


}

void Core3_Init(){
    PrintChar(core3);
}

