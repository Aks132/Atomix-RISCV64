/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"



int main(){

    PrintChar(boot);
    PrintDigit(hartid1);
    return 0;
}

void Core0_Init(){
    PrintChar(core0);
}


void Core1_Init(){
    PrintChar(core1);

}

void Core2_Init(){
    PrintChar(core2);

}

void Core3_Init(){
    PrintChar(core3);
}

