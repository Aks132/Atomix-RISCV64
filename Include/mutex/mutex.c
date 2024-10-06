#include "mutex.h"
#include "../include/libc/bool.h"
#include "../include/core/core.h"



// Inline atomic exchange function
static inline int atomic_exchange(volatile int *ptr, int newval) {
    int result;
    asm volatile("amoswap.w %0, %2, %1"
                 : "=r"(result), "+A"(*ptr)
                 : "r"(newval)
                 : "memory");
    return result;
}

// Initialize the mutex
void mutex_init(mutex_t *mutex, char *name) {
    mutex->lock = 0;  // 0 means unlocked
    mutex->name = name;
    mutex->owner_thread_id = -1;  // No owner initially
    mutex->recursive_count = 0;   // No recursive locks initially
}

// Lock the mutex
void mutex_lock(mutex_t *mutex) {
    int thread_id = tp_read(); // Get current thread ID
    
    DisableInterrupt(); // Disable interrupts to prevent race conditions

    // Handle recursive locking
    if (mutex->owner_thread_id == thread_id) {
        mutex->recursive_count++;
        EnableInterrupt(); // Re-enable interrupts
        return; // No need to lock again
    }

    // Spinlock with optional yield to avoid busy-waiting
    while (__sync_lock_test_and_set(&mutex->lock, 1) != 0) {
        // Uncomment and replace with a proper yield/sleep function
        // yield();  // Consider implementing a yield function to reduce CPU usage
    }
    
    // Set ownership and count
    mutex->owner_thread_id = thread_id;  
    mutex->recursive_count = 1;           
    __sync_synchronize(); // Ensure memory visibility
    
    EnableInterrupt(); // Re-enable interrupts
}

// Unlock the mutex
void mutex_unlock(mutex_t *mutex) {
    int thread_id = mhartid(); // Get current thread ID

    DisableInterrupt(); // Disable interrupts to prevent race conditions
    
    // Ensure the mutex is owned by the current thread
    if (mutex->owner_thread_id != thread_id) {
        EnableInterrupt(); // Re-enable interrupts
        return; // Exit without unlocking
    }
    
    // Handle recursive unlock
    if (--mutex->recursive_count == 0) {
        // Release the lock and reset ownership
        mutex->owner_thread_id = -1;
        __sync_synchronize();  // Ensure memory visibility
        __sync_lock_release(&mutex->lock);  // Release the lock
    }
    
    EnableInterrupt(); // Re-enable interrupts
}

// Initialize the semaphore
void sem_init(semaphore_t *sem, int initial_count) {
    sem->count = initial_count;
    mutex_init(&sem->mutex, "semaphore_mutex");
}

// Wait on the semaphore
void sem_wait(semaphore_t *sem) {
    while (1) {
        mutex_lock(&sem->mutex);
        if (sem->count > 0) {
            sem->count--;
            mutex_unlock(&sem->mutex);
            break;
        }
        mutex_unlock(&sem->mutex);
        // yield(); // Consider yielding CPU to avoid busy-waiting
    }
}

// Signal the semaphore
void sem_signal(semaphore_t *sem) {
    mutex_lock(&sem->mutex);
    sem->count++;
    mutex_unlock(&sem->mutex);
}

