/* chapter 7: of RISC-V-SPEC-v2.2 

rs1: The address of the memory location (your lock variable, ptr).
rs2: The value to swap in (your new value, newval).
rd: The register where the original value will be stored (in this case, result).

%0 corresponds to result (the output).
%1 corresponds to *ptr (the memory address of the lock).
%2 corresponds to newval (the value to be swapped in).

link : https://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Atomic-Builtins.html


*/
#include "mutex.h"
#include "libc/bool.h"
#include "core/core.h"

 void mutex_init(mutex_t *mutex , char*  name) {
    mutex->lock = 0;  // 0 means unlocked
    mutex->name = name;
}

void mutex_lock(mutex_t* lock)
{
  DisableInterrupt(); // disable interrupts to avoid deadlock.
  while(__sync_lock_test_and_set(&lock->lock, 1) != 0);
  __sync_synchronize();

}

// Release the lock.
void
mutex_unlock(mutex_t* lock)
{
  __sync_synchronize();
  __sync_lock_release(&lock->lock);
  EnableInterrupt();
}