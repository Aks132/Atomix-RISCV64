#ifndef __START_H__
#define __START_H__
/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "libc/Wprintf.h"
#include "libc/bool.h"

extern unsigned int hartid0;
extern unsigned int hartid1;
extern unsigned int hartid2;
extern unsigned int hartid3;
void Core0_Init();
void Core1_Init();
void Core2_Init();
void Core3_Init();

extern const char *core0 ;
extern const char *core1;
extern const char *core2  ;
extern const char *core3 ;
extern const char *AllCoreBootsUp ;

#endif //__START_H__

