<<<<<<< HEAD
#pragma once
=======
#ifndef __START_H__
#define __START_H__
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
/*
    Here we have to configure uart and interrupt IG(if they are not disabled by default)
*/
#include "sysprints.h"
#include "libc/Wprintf.h"
#include "libc/bool.h"
<<<<<<< HEAD
#include "mutex/mutex.h"
#include "core/core.h"
=======

>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
extern unsigned int hartid0;
extern unsigned int hartid1;
extern unsigned int hartid2;
extern unsigned int hartid3;
void Core0_Init();
void Core1_Init();
void Core2_Init();
void Core3_Init();

<<<<<<< HEAD
=======
#endif //__START_H__
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241

