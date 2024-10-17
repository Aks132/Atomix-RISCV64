#include "mutex.h"
#include "libc/bool.h"
#include "core/core.h"

 void mutex_init(mutex_t *mutex , char*  name) {
    mutex->locked = 0;  // 0 means unlocked
    mutex->name = name;
}

void mutex_lock(mutex_t* lock)
{
  DisableInterrupt(); // disable interrupts to avoid deadlock.
  while(__sync_lock_test_and_set(&lock->locked, 1) != 0);
  __sync_synchronize();

}

// Release the lock.
void
mutex_unlock(mutex_t* lock)
{
  __sync_synchronize();
  __sync_lock_release(&lock->locked);
  EnableInterrupt();
}