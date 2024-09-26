/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"



int main(){
    

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

