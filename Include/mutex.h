#pragma once

typedef struct {
    volatile int lock;
    char* name ;
} mutex_t;

void mutex_init(mutex_t *mutex , char* name);
void mutex_lock(mutex_t *mutex);
int  mutex_trylock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);

