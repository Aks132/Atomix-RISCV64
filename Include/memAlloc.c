#include "memAlloc.h"
#include "core/core.h"


extern unsigned long _end_;
extern unsigned long FINAL_END[];
extern unsigned long _text_start[];


inline unsigned long mem_round_upto_pages(unsigned long memTobeAllign) {
    return (memTobeAllign + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

void PageTraversal(void *physicalADDRstart , void* physicalADDRend){

    Println();
    char* currenttraversalPointer = (char*)mem_round_upto_pages((unsigned long) physicalADDRstart);
    // my_printf("Current traversal pointer \n");
    // my_printf("%d\n",(char*)currenttraversalPointer);
    Println();

    char* endofaddr = (char*)physicalADDRend;
    // my_printf("I am end of addr \n");
    // my_printf("%d\n",(char*)endofaddr);
    // Println();

    // my_printf("I am here");
    // Println();
    // my_printf("%d\n",PAGE_SIZE);
    for(; currenttraversalPointer + PAGE_SIZE <= (char*)endofaddr; currenttraversalPointer += PAGE_SIZE){
        freememory(currenttraversalPointer);
        static int freememcall = 0 ;
        UNUSED(freememcall);
        // my_printf(" currenttraversalPointer insiode for %d\n",(char*)currenttraversalPointer);
        // my_printf("Free memory function call counter %d\n" , freememcall++);
    }

}
struct kernel_mem_manager memLock;
void freememory (void *mem){

    TraverseThroughMemory_t *freemem;
    // mutex_lock(&memLock.lock);
    my_memset(mem,69,PAGE_SIZE);
    freemem = (struct TraverseThroughMemory *)mem;
    // lib_puts("Freeeing the tables\n");
    freemem->next = memLock.freemem;
    memLock.freemem = freemem;
    //freemem is poining to the last poiter in mem , and all thhe pages are linked withh linked list
    // mutex_unlock(&memLock.lock);
    // my_printf("%d\n",freemem);

}

void kernel_mem_init(){
    // Initialise locks for mem handling !!
    my_printf("kernel mem init done\n");
    mutex_init(&memLock.lock , "memelock");
    // We have to make mem amd specify the page table as till now we have not performed any mem operation!
    // memLock.lock.lock = 1;
    // my_printf("%d",memLock.lock);
    // char* ptr = (char*)_end_;
    // *ptr = 123;
    // my_printf("%d\n",*ptr);

    // my_printf("%p",&ptr);
    // my_printf("%p",test);
    // my_printf("%d",((void*)_end_));
    // char *x = 0x88000000;
    // my_printf("%d",x);
    // my_printf("before page traversal \n");
    // my_printf("end ......%d\n" , &_end_);

    PageTraversal((void*)&_end_, (void*)KERNELEND);

}

void* memory_alloc(){
    TraverseThroughMemory_t *freemem;

    freemem = memLock.freemem;
    if(freemem) // if freemem is not pointing to 0 that means we have pages to allocate mem
    {
        // allocate page and set freemem->next pointer to next location
        // that means previous page is used 
        memLock.freemem = freemem->next;
        my_memset((char*)freemem , 69 , PAGE_SIZE); // to debug !
    }

    return (void *)freemem;

}

void  *my_memset(void *b, int c, int len)
{
  unsigned char *p = b;
  while(len > 0)
    {
      // my_printf(" i am in memset\n");
      *p = c;
      p++;
      len--;
    }
  return(b);
}