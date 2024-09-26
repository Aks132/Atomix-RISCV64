/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "../Include/sysprints.h"
#include "../Include/extras.h"
#include "../include/libc/Wprintf.h"
#include "../include/systemaddr.h"



int main(){

    PrintChar(boot);
    PrintDigit(hartid);


    return 0;
}
