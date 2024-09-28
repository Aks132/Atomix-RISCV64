#include "start.h"
#include "../Include/mutex.h"
const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";

mutex_t my_mutex;

void Core0_Init(){
    mutex_lock(&my_mutex);
    Println();
    PrintChar(core0);
    Println();
    mutex_unlock(&my_mutex);
    main();
}

void Core1_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core1);
    Println();
    mutex_unlock(&my_mutex);
    main();
}

void Core2_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core2);
    Println();
    mutex_unlock(&my_mutex);
    main();
}

void Core3_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core3);
    Println();
    mutex_unlock(&my_mutex);
    main();
}
