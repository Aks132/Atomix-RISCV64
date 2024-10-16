#ifndef _MUTEX_H
#define _MUTEX_H

// Mutual exclusion lock.
typedef struct mutex{

   volatile int locked;   
   char* name;    

}mutex_t;

void mutex_init(mutex_t *mutex , char* name);
void mutex_lock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);


#endif //_MUTEX_H

