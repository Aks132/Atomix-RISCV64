#pragma once


#include "../Include/memAlloc.h"
#include "../Include/uart/uart.h"
#include "../Include/core/core.h"
void map_page(unsigned long* pagetabledatastruct , unsigned long virtualAddr , unsigned long physicAddr , unsigned long permissionBits);
unsigned long* makepagetable();
void SetupPaging();