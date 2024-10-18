#ifndef __PAGES_H__
#define __PAGES_H__


#include "memAlloc.h"
#include "uart/uart.h"
#include "core/core.h"
#include "systemaddr.h"
<<<<<<< HEAD
=======

>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms);
void maketable();
unsigned long *setupPagetable();
unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check);
void maketable();

#endif //__PAGES_H__


