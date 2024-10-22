#pragma once
/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "libc/Wprintf.h"
#include "libc/bool.h"
#include "mutex/mutex.h"
#include "core/core.h"
#include "mtime/mtime.h"
extern unsigned int hartid0;
extern unsigned int hartid1;
extern unsigned int hartid2;
extern unsigned int hartid3;
void Core0_Init();
void Core1_Init();
void Core2_Init();
void Core3_Init();


