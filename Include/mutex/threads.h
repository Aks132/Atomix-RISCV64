#ifndef THREADS_H
#define THREADS_H

#define MAX_THREADS 4  // Maximum number of threads

// Define the different states a thread can have
typedef enum {
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_SUSPENDED,
    THREAD_TERMINATED
} thread_state_t;

// Define the thread descriptor structure
typedef struct _pthread_descr_struct {
    int p_tid;                         // Thread ID
    thread_state_t state;              // Thread's current state (e.g., running, suspended)
    void (*entry_point)(void *);       // The function the thread will execute
    void *arg;                         // The argument to be passed to the thread function
    struct _pthread_descr_struct *p_nextwaiting; // Pointer to the next thread in a wait queue
    void *stack_pointer;               // Stack pointer for context switching
} pthread_descr;

extern pthread_descr threads[MAX_THREADS];  // Global thread array

// Function prototypes for thread management
void init_thread_system();                       // Initialize the thread system
void create_thread(void (*entry_point)(void *), void *arg); // Create a thread
void switch_to_next_thread();                    // Switch to the next thread (scheduler)
void suspend(pthread_descr *self);               // Suspend the current thread
void restart(pthread_descr *thread);             // Restart (resume) a suspended thread

// Internal function to perform context switch
void context_switch(void **old_sp, void **new_sp);

#endif // THREADS_H
