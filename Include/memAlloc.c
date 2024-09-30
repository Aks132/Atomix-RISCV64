#include "../Include/memAlloc.h"


extern unsigned long _end_;
extern unsigned long FINAL_END[];
extern unsigned long _text_start[];
#define test 0x10000
static int nu_of_pages = 0;
inline unsigned long mem_round_upto_pages(unsigned long memTobeAllign) {
    return (memTobeAllign + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

void PageTraversal(void *physicalADDRstart , void* physicalADDRend){

    Println();
    char* currenttraversalPointer = (char*)mem_round_upto_pages((unsigned long) physicalADDRstart);
    my_printf("Current traversal pointer \n");
    my_printf("%d",(void*)currenttraversalPointer);
    Println();

    char* endofaddr = (char*)physicalADDRend;
    my_printf("I am end of addr \n");
    my_printf("%x",(void*)endofaddr);
    Println();

    my_printf("I am here");
    Println();
    my_printf("%d",PAGE_SIZE);
    for(; currenttraversalPointer + PAGE_SIZE <= (char*)endofaddr; currenttraversalPointer += PAGE_SIZE){
        freememory(currenttraversalPointer);
    }

}
struct kernel_mem_manager memLock;
void freememory (void *mem){

    TraverseThroughMemory_t *freemem;
    mutex_lock(&memLock.lock);
    my_memset(mem,69,PAGE_SIZE);
    Println();
    freemem = (struct TraverseThroughMemory *)mem;
    lib_puts("Freeeing the tables\n");
    freemem->next = memLock.freemem;
    memLock.freemem = freemem;
    mutex_unlock(&memLock.lock);

}

void kernel_mem_init(){
    // Initialise locks for mem handling !!
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
    PageTraversal((void*)_end_, (void*)KERNELEND);
 
}
