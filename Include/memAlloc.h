#pragma once

#include "../Include/uart/uart.h"
#include "../Include/mutex/mutex.h"
#include "../Include/libc/Wprintf.h"

#define BASEADDDRKERNEL 0x80000000UL
<<<<<<< HEAD
#define KERNELEND 		(BASEADDDRKERNEL + (128*1024*1024)) 
#define PAGE_SIZE 		 4096

void  *my_memset(void *b, int c, int len)
{
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      // my_printf(" i am in memset\n");
      *p = c;
      p++;
      len--;
    }
  return(b);
}

=======
#define KERNELEND 		  (BASEADDDRKERNEL + (128*1024*1024)) 
#define PAGE_SIZE 		  4096
//16777216
//
void  *my_memset(void *b, int c, int len);
>>>>>>> temp-branch

typedef struct TraverseThroughMemory
{
	struct TraverseThroughMemory *next;

}TraverseThroughMemory_t;

struct kernel_mem_manager{
  mutex_t lock;
  struct TraverseThroughMemory *freemem; // initially will point to NULL
};

unsigned long mem_round_upto_pages(unsigned long memTobeAllign);
void kernel_mem_init();
void PageTraversal(void *physicalADDRstart , void* physcalADDRend);
void freememory (void *mem);
void* memory_alloc();
void kernel_mem_init();