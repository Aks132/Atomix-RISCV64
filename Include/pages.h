#pragma once


#include "../Include/memAlloc.h"
#include "../Include/uart/uart.h"
#include "../Include/core/core.h"
#include "../Include/systemaddr.h"
void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms);
// unsigned long* makepagetable();
unsigned long *setupPagetable();
unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check);