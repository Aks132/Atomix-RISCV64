#include "pages.h"
/*
	My basic intutition to do this 

	* page table is just represention of pages in memory 
	* so it will just return a memory location (means a pointer to a specifc memory)

CURRENT LOCATION --->>      | Page 1 | 
NEXT CURRENT LOCATION -->	| Page 2 | -> Next location counter will shift here if we use a page 
							| Page 3 |
							|
							|
							|
							|
							|
							|
							|


Now we will take page of memory(means pointer to it) and use it to map(or create a page table)

That meas our page table should be of some data type (for now unsigned long *)

so we will use malloc to to take mem of 4096 byte and use that mem to map thhings

*/ 
extern char _text_end[];

#define MASKNINEBIT          0x1FF // 9 bits
#define PHYSICALSHIFT(level)  (12+(9*(level)))
#define PX(level, va) ((((unsigned long) (va)) >> PHYSICALSHIFT(level)) & MASKNINEBIT)

unsigned long * k_pagetable;
void maketable(){
	k_pagetable = setupPagetable();
	asm volatile("sfence.vma zero, zero");
	satp_write(((8L << 60) | (((unsigned long)k_pagetable) >> 12)));
	asm volatile("sfence.vma zero, zero");
}
unsigned long *setupPagetable(){

	unsigned long * pagetable;
	pagetable = (unsigned long*)memory_alloc();
	my_memset(pagetable , 0 , PAGE_SIZE);
	map_pages(pagetable,(unsigned long)UART_TX_ADDR,(unsigned long)UART_TX_ADDR,4096,((1<<1)|(1<<2)));
	map_pages(pagetable, KERNBASE, KERNBASE, mem_round_upto_pages((unsigned long)_text_end-KERNBASE), ((1<<1)|(1<<3)));
	map_pages(pagetable , (unsigned long) _text_end , (unsigned long) _text_end  , KERNELEND - (unsigned long) _text_end , ((1<<1)|(1<<2)));
	mapping_process_kernelstack(pagetable);
	return pagetable;
}

void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms){
	unsigned long start = 0 ; 
	unsigned long end ;   
	unsigned long *PTE;
	end = virtAddr + size - PAGE_SIZE;
	start =( unsigned long )virtAddr;
  for(;;){
    if((PTE = moveThroughPages(pagetable, start, 1)) == 0){
    	return;}
    if(*PTE & (1<<0))
      my_printf(" i am panicked : mappages: remap\n");
    *PTE = ((((((unsigned long)phyAddr) >> 12) << 10)) | perms | (1<<0));
    unsigned long x = phyAddr;
	UNUSED(x);
    if(start == end){
      break;
      
    }
    start =  start + PAGE_SIZE;
    phyAddr =phyAddr  + PAGE_SIZE;

  }
}


unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check){
	for(int i = 2 ; i > 0 ; i--){
		unsigned long* pte = &pages[PX(i,virtAddr)];
		if(*pte  & (1<<0)){
			pages = (unsigned long *)(((*pte) >> 10) << 12);
		}
		else {
      if(!check || (pages = (unsigned long*)memory_alloc()) == 0)
        return 0;
      my_memset(pages, 0, PAGE_SIZE);
      *pte = (((((unsigned long)pages) >> 12) << 10)) | (1<<0);
    }
	}
	return &pages[PX(0,virtAddr)];
}

