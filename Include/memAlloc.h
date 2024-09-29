#pragma once
#include "../Include/systemaddr.h"
#include "../Include/mutex.h"
#include "../Include/mutex.h"


void  *my_memset(void *b, int c, int len)
{
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      PrintChar("writing 69 \n");
      *p = c;
      p++;
      len--;
    }
  return(b);
}


typedef struct TraverseThroughMemory
{
	struct TraverseThroughMemory *next;

}TraverseThroughMemory_t;

struct kernel_mem_manager{
  mutex_t lock;
  struct TraverseThroughMemory *freemem;
};

unsigned long mem_round_upto_pages(unsigned long memTobeAllign);
void kernel_mem_init();
void PageTraversal(void *physicalADDRstart , void* physcalADDRend);
void freememory (void *mem);