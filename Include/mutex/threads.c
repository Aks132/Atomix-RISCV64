#include "mutex/threads.h"
#include "mutex/mutex.h" // Ensure mutex integration with threads

// Global thread array and current thread pointer
pthread_descr threads[MAX_THREADS];
pthread_descr *current_thread = (pthread_descr *)0;
pthread_descr *next_thread = (pthread_descr *)0;
int current_thread_id = 0;
int num_threads = 0;

// Initialize the thread system
void init_thread_system() {
    num_threads = 0;
    current_thread = (pthread_descr *)0;
    next_thread = (pthread_descr *)0;
    
    // Initialize each thread as terminated and unassigned
    for (int i = 0; i < MAX_THREADS; i++) {
        threads[i].p_tid = 0;
        threads[i].state = THREAD_TERMINATED;
        threads[i].p_nextwaiting = (pthread_descr *)0;
        threads[i].stack_pointer = (void *)0;
    }
}

// Create a new thread
void create_thread(void (*entry_point)(void *), void *arg) {
    if (num_threads < MAX_THREADS) {
        pthread_descr *new_thread = &threads[num_threads++];
        new_thread->p_tid = num_threads;
        new_thread->state = THREAD_READY;
        new_thread->entry_point = entry_point;
        new_thread->arg = arg;
        new_thread->p_nextwaiting = (pthread_descr *)0;

        // Allocate stack for context switching (to be implemented based on your system)
        new_thread->stack_pointer = (void *)0; // You need to allocate stack space here

        if (current_thread == (pthread_descr *)0) {
            // If this is the first thread, set it as the current thread
            current_thread = new_thread;
            new_thread->state = THREAD_RUNNING;
        }
    }
}

// Switch to the next thread (simple round-robin scheduler)
void switch_to_next_thread() {
    int next_thread_id = (current_thread_id + 1) % num_threads;
    next_thread = &threads[next_thread_id];

    if (next_thread->state != THREAD_TERMINATED) {
        next_thread->state = THREAD_RUNNING;
        pthread_descr *prev_thread = current_thread;
        current_thread = next_thread;
        current_thread_id = next_thread_id;

        // Perform context switch
        context_switch(&prev_thread->stack_pointer, &current_thread->stack_pointer);
    }
}

// Suspend the current thread
void suspend(pthread_descr *self) {
    self->state = THREAD_SUSPENDED;
    switch_to_next_thread();
}

// Restart (resume) a suspended thread
void restart(pthread_descr *thread) {
    if (thread->state == THREAD_SUSPENDED) {
        thread->state = THREAD_READY;
    }
}

// Context switch (architecture-specific)
void context_switch(void **old_sp, void **new_sp) {
    // Save the current stack pointer (old_sp) and restore the new stack pointer (new_sp)
    // This function should implement architecture-specific context switching,
    // such as saving and restoring registers and switching stacks.
}
