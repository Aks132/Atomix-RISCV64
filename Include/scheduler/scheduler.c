#include "scheduler.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

struct task *task_list = NULL;
struct task *current_task = NULL;
int task_count = 0;

#define STACK_SIZE 0x1000
#define STACK_ALIGNMENT 16

void init_scheduler() {
    // Initialize the task list to NULL (empty task list)
    task_list = NULL;
    
    // Set the current task pointer to NULL initially
    current_task = NULL;
    
    // Initialize any other scheduler-related structures if needed
    task_count = 0;
}


uint64_t allocate_stack() {
    static uint64_t stack_base = 0x80001000;
    stack_base += STACK_SIZE;
    stack_base = (stack_base + STACK_ALIGNMENT - 1) & ~(STACK_ALIGNMENT - 1);
    return stack_base;
}

uint64_t allocate_task_control_block() {
    static uint64_t task_memory_base = 0x81000000;
    uint64_t tcb_address = task_memory_base;
    task_memory_base += sizeof(struct task);
    return tcb_address;
}

void create_task(void (*task_function)(), uint64_t pid) {
    if (task_count >= MAX_TASKS) {
        my_printf("Max tasks reached. Task %lu not created.\n", pid);
        return;
    }
    
    struct task *new_task = (struct task *)allocate_task_control_block();
    
    new_task->pid = pid;
    new_task->stack_pointer = allocate_stack();
    new_task->program_counter = (uint64_t)task_function;
    new_task->state = TASK_READY;

    if (task_list == NULL) {
        task_list = new_task;
        new_task->next = new_task;
    } else {
        struct task *temp = task_list;
        while (temp->next != task_list) {
            temp = temp->next;
        }
        temp->next = new_task;
        new_task->next = task_list;
    }

    task_count++;
    my_printf("Task %lu created and added to task list\n", pid);
}

void save_context(struct task *t) {
    // Save stack pointer (SP)
    asm volatile ("mv %0, sp" : "=r"(t->stack_pointer));
    
    // Save program counter (PC)
    asm volatile ("auipc %0, 0" : "=r"(t->program_counter));

    // Save general-purpose registers manually (x1 to x31)
    asm volatile ("mv %0, ra" : "=r"(t->cpu_registers[1]));   // Save return address (x1)
    asm volatile ("mv %0, t0" : "=r"(t->cpu_registers[5]));   // Save temporary register (x5)
    asm volatile ("mv %0, t1" : "=r"(t->cpu_registers[6]));   // Save temporary register (x6)
    asm volatile ("mv %0, t2" : "=r"(t->cpu_registers[7]));   // Save temporary register (x7)
    // Repeat for all other registers you want to save...
}
void restore_context(struct task *t) {
    // Restore stack pointer (SP)
    asm volatile ("mv sp, %0" :: "r"(t->stack_pointer));
    
    // Restore program counter (PC)
    asm volatile ("jr %0" :: "r"(t->program_counter));

    // Restore general-purpose registers manually (x1 to x31)
    asm volatile ("mv ra, %0" :: "r"(t->cpu_registers[1]));   // Restore return address (x1)
    asm volatile ("mv t0, %0" :: "r"(t->cpu_registers[5]));   // Restore temporary register (x5)
    asm volatile ("mv t1, %0" :: "r"(t->cpu_registers[6]));   // Restore temporary register (x6)
    asm volatile ("mv t2, %0" :: "r"(t->cpu_registers[7]));   // Restore temporary register (x7)
    // Repeat for all other registers you want to restore...
}
void schedule() {
    save_context(current_task);
    current_task = current_task->next;
    restore_context(current_task);
}

void start_scheduler() {
    if (task_list != NULL) {
        current_task = task_list;
        restore_context(current_task);
    }
}
