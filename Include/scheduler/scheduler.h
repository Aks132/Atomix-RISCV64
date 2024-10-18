#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "libc/types.h"
#include "libc/Wprintf.h"

#define MAX_TASKS 10

// Task state definitions using enum for clarity
typedef enum {
    TASK_READY = 0,    // Task is ready to run
    TASK_RUNNING = 1,  // Task is currently running
    TASK_WAITING = 2   // Task is waiting for a resource
} task_state_t;

// Task Control Block (TCB) structure
// Task Control Block (TCB) structure
struct task {
    uint64_t pid;                 // Process ID
    uint64_t stack_pointer;        // Stack pointer (SP)
    uint64_t program_counter;      // Program counter (PC)
    uint64_t cpu_registers[32];    // Array to save the 32 general-purpose registers
    task_state_t state;            // Task state: Ready, Running, Waiting
    struct task *next;             // Pointer to the next task in the round-robin queue
};

// Function declarations for task management
void init_scheduler();
void create_task(void (*task_function)(), uint64_t pid);  // Creates a new task
void schedule();                                           // Scheduler function
void save_context(struct task *t);                         // Saves the context of a task
void restore_context(struct task *t);                      // Restores the context of a task
void start_scheduler();                                    // Starts the task scheduler

// Memory management functions
uint64_t allocate_stack();   // Allocates memory for a task's stack

#endif // SCHEDULER_H
