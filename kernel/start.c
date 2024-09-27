/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"

#include "mutex.h"

mutex_t my_mutex;

void shared_resource() {
    mutex_lock(&my_mutex);
    
    // Critical section: UART logging
    UART_SEND("Lock acquired, modifying shared resource...\n");

    // Simulate some work
    for (volatile int i = 0; i < 1000000; i++);

    UART_SEND("Releasing lock...\n");

    mutex_unlock(&my_mutex);
}

int main(){
    mutex_init(&my_mutex);

    UART_SEND("Starting kernel...\n");

    // Simulate concurrent access to a shared resource
    shared_resource();
    shared_resource();  // Test the locking mechanism

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
        main();
}


void Core1_Init(){
    PrintChar(core1);
        main();

}

void Core2_Init(){
    PrintChar(core2);
        main();

}

void Core3_Init(){
    PrintChar(core3);
        main();
}

