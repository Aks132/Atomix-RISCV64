#ifndef MUTEX_H
#define MUTEX_H

#include "../include/libc/bool.h"

// Mutex structure definition
typedef struct {
    volatile int lock;               // Lock variable (0 = unlocked, 1 = locked)
    char *name;                      // Mutex name for debugging purposes
    int owner_thread_id;             // ID of the thread that owns the mutex
    int recursive_count;             // Count of recursive locks
} mutex_t;

// Semaphore structure definition
typedef struct semaphore {
    int count;
    mutex_t mutex;
} semaphore_t;

// Function prototypes for Mutex
void mutex_init(mutex_t *mutex, char *name);
void mutex_lock(mutex_t *mutex);
int mutex_trylock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);

// Function prototypes for Semaphore
void sem_init(semaphore_t *sem, int value);
void sem_wait(semaphore_t *sem);
void sem_signal(semaphore_t *sem);

// Stub for priority inversion handling
void handle_priority_inversion(mutex_t *mutex, int requesting_thread_priority);

#endif // MUTEX_H
