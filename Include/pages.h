#ifndef __PAGES_H__
#define __PAGES_H__


#include "memAlloc.h"
#include "uart/uart.h"
#include "core/core.h"
#include "systemaddr.h"

void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms);
// unsigned long* makepagetable();
unsigned long *setupPagetable();
unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check);


#endif //__PAGES_H__


