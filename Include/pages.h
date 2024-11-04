#pragma once


#include "memAlloc.h"
#include "uart/uart.h"
#include "core/core.h"
#include "systemaddr.h"
#include "process.h"
void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms);
void maketable();
unsigned long *setupPagetable();
unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check);