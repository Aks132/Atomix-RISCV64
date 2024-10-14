#include "mutex/mutex.h"

// Initialize the mutex
void mutex_init(mutex_t *mutex) {
    mutex->m_spinlock = 0;  // Spinlock is free
    mutex->m_count = 0;     // Mutex is unlocked
    mutex->m_owner = -1;    // No owner initially
    queue_init(&mutex->m_waiting);  // Initialize the waiting queue
}

// Lock the mutex, blocking if necessary
void mutex_lock(mutex_t *mutex, pthread_descr *self) {
    acquire(&mutex->m_spinlock);  // Acquire the spinlock for atomic operation

    if (mutex->m_count == 0) {
        // Mutex is free, lock it
        mutex->m_count = 1;
        mutex->m_owner = self->p_tid;
        release(&mutex->m_spinlock);  // Release the spinlock
    } else {
        // Mutex is locked, put the thread in the waiting queue
        enqueue(&mutex->m_waiting, self);
        release(&mutex->m_spinlock);  // Release the spinlock
        suspend(self);  // Suspend the thread until it's woken up
    }
}

// Unlock the mutex and wake up a waiting thread if any
void mutex_unlock(mutex_t *mutex, pthread_descr *self) {
    acquire(&mutex->m_spinlock);  // Acquire the spinlock for atomic operation

    if (mutex->m_owner == self->p_tid) {
        // The thread is the owner of the mutex
        pthread_descr *next_thread = dequeue(&mutex->m_waiting);
        if (next_thread != (pthread_descr *)0) {
            // Wake up the next thread in the queue
            restart(next_thread);
        } else {
            // No threads waiting, simply unlock the mutex
            mutex->m_count = 0;
            mutex->m_owner = -1;
        }
    }
    
    release(&mutex->m_spinlock);  // Release the spinlock
}

// Initialize a waiting queue
void queue_init(pthread_queue *q) {
    q->head = (pthread_descr *)0;
    q->tail = (pthread_descr *)0;
}

// Enqueue a thread into the waiting queue
void enqueue(pthread_queue *q, pthread_descr *th) {
    th->p_nextwaiting = (pthread_descr *)0;
    if (q->tail == (pthread_descr *)0) {
        q->head = th;
        q->tail = th;
    } else {
        q->tail->p_nextwaiting = th;
        q->tail = th;
    }
}

// Dequeue a thread from the waiting queue
pthread_descr *dequeue(pthread_queue *q) {
    pthread_descr *th = q->head;
    if (th != (pthread_descr *)0) {
        q->head = th->p_nextwaiting;
        if (q->head == (pthread_descr *)0) {
            q->tail = (pthread_descr *)0;
        }
        th->p_nextwaiting = (pthread_descr *)0;
    }
    return th;
}

// Acquire a spinlock (busy-wait)
void acquire(int *spinlock) {
    while (__sync_lock_test_and_set(spinlock, 1)) {
        // Busy wait until the spinlock becomes free
    }
}

// Release a spinlock
void release(int *spinlock) {
    __sync_lock_release(spinlock);  // Release the spinlock
}
