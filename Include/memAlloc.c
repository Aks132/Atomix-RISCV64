#include "../Include/memAlloc.h"

// #define BASEADDDRKERNEL 0x80000000L
const unsigned long BASEADDDRKERNEL =  0x80000000;

 unsigned long KERNELEND = BASEADDDRKERNEL + (1024*1024*128);
const unsigned long PAGE_SIZE      = 4096;


extern unsigned long _end_;
extern unsigned long _text_start;
#define test 10000
int nu_of_pages;
inline unsigned long mem_round_upto_pages(unsigned long memTobeAllign) {
    return (memTobeAllign + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

void PageTraversal(void *physicalADDRstart , void* physicalADDRend){
    char* currenttraversalPointer;
    currenttraversalPointer = (char*)mem_round_upto_pages((unsigned long) physicalADDRstart);
    char* endofaddr = (char*)physicalADDRend;
    PrintChar("Start Address: ");
    PrintDigit((unsigned long)currenttraversalPointer);
    PrintChar(" End Address: ");
    PrintDigit((unsigned long)endofaddr);


    // for(; currenttraversalPointer + PAGE_SIZE <= (char*)endofaddr; currenttraversalPointer += PAGE_SIZE){
    //     freememory(currenttraversalPointer);
    //     PrintDigit(nu_of_pages++);
    //     Println();
    //     PrintChar("Going though pages\n");
    // }

}
struct kernel_mem_manager memLock;
void freememory (void *mem){

    TraverseThroughMemory_t *freemem;
    mutex_lock(&memLock.lock);
    my_memset(mem,69,PAGE_SIZE);
    Println();
    freemem = (struct TraverseThroughMemory *)mem;
    PrintChar("Freeeing the tables\n");
    freemem->next = memLock.freemem;
    memLock.freemem = freemem;
    mutex_unlock(&memLock.lock);

}

void kernel_mem_init(){
    // Initialise locks for mem handling !!
    // mutex_init(&memLock.lock , "memelock");
    // We have to make mem amd specify the page table as till now we have not performed any mem operation!

    PrintDigit(BASEADDDRKERNEL);
    Println();
    // PrintHex(*basekernel);
    // PageTraversal(_end_ , (void*)KERNELOND);
}
