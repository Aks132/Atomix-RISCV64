#ifndef __MUTEX_H__
#define __MUTEX_H__

typedef struct {
    volatile int lock;
} mutex_t;

void mutex_init(mutex_t *mutex);
void mutex_lock(mutex_t *mutex);
int  mutex_trylock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);

#endif
