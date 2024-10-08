#include "mutex.h"
#include "../include/libc/bool.h"
#include "../include/core/core.h"

/* chapter 7: of RISC-V-SPEC-v2.2 

rs1: The address of the memory location (your lock variable, ptr).
rs2: The value to swap in (your new value, newval).
rd: The register where the original value will be stored (in this case, result).

%0 corresponds to result (the output).
%1 corresponds to *ptr (the memory address of the lock).
%2 corresponds to newval (the value to be swapped in).

link : https://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Atomic-Builtins.html


*/
static inline int atomic_exchange(volatile int *ptr, int newval) {
    int result;
    asm volatile("amoswap.w %0, %2, %1"
                 : "=r"(result), "+A"(*ptr)
                 : "r"(newval)
                 : "memory");
    return result;
}

void mutex_init(mutex_t *mutex , char*  name) {
    mutex->lock = 0;  // 0 means unlocked
    mutex->name = name;
}

void mutex_lock(mutex_t  *mutex)
{
  DisableInterrupt();
  while(__sync_lock_test_and_set(&mutex->lock, 1) != 0);
  __sync_synchronize();
  EnableInterrupt();

}

int mutex_trylock(mutex_t *mutex) {
    return atomic_exchange(&mutex->lock, 1) == 0;  // Return true if lock is acquired
}

void mutex_unlock(mutex_t *mutex) {
    mutex->lock = 0; // Correctly release the lock
    __sync_synchronize (); 


}