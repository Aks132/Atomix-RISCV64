#ifndef MUTEX_H
#define MUTEX_H

#include "mutex/threads.h" // Include thread management for thread descriptors

// Structure for the thread waiting queue
typedef struct _pthread_queue {
    pthread_descr *head;  // First element in the queue
    pthread_descr *tail;  // Last element in the queue
} pthread_queue;

// Mutex structure definition
typedef struct {
    volatile int m_spinlock;      // Spinlock for atomic operations
    int m_count;                  // 0 if unlocked, 1 if locked
    int m_owner;                  // Thread ID of the current owner
    pthread_queue m_waiting;      // Queue for waiting threads
} mutex_t;

// Function prototypes
void mutex_init(mutex_t *mutex);                     // Initialize mutex
void mutex_lock(mutex_t *mutex, pthread_descr *self);  // Lock the mutex
void mutex_unlock(mutex_t *mutex, pthread_descr *self); // Unlock the mutex

// Queue management function prototypes
void queue_init(pthread_queue *q);                   // Initialize a queue
void enqueue(pthread_queue *q, pthread_descr *th);    // Add thread to queue
pthread_descr *dequeue(pthread_queue *q);             // Remove thread from queue

// Spinlock helper functions
void acquire(int *spinlock);                         // Acquire the spinlock
void release(int *spinlock);                         // Release the spinlock

#endif // MUTEX_H
