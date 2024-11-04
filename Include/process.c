#include "process.h"
process_t alllprocess[NUMNER_OF_THREAD];
void  AllProcessInit(){
    struct process *head_proc;
    for(head_proc = alllprocess ; head_proc < &alllprocess[NUMNER_OF_THREAD] ; head_proc++ ){
        head_proc->current_state = idle;
        head_proc->kernel_sp  = (TRAMPOLINE_COMMMON_REGION  - ((head_proc - alllprocess) + 1) * 2 * PAGE_SIZE);
        head_proc->dead = 0;
    }
}
void mapping_process_kernelstack(unsigned long* page){

    struct process *head_proc;
    for(head_proc = alllprocess ; head_proc < &alllprocess[NUMNER_OF_THREAD] ; head_proc++ ){
        char* mem = memory_alloc(); // do a sanity check for mem allocationw
        unsigned long virtualAddr = (TRAMPOLINE_COMMMON_REGION  - ((head_proc - alllprocess) + 1) * 2 * PAGE_SIZE);
        map_pages(page , virtualAddr , (unsigned long)mem , PAGE_SIZE , (1<<1)|(1<<2));
    }
}