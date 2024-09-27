#include "mutex.h"
#include "stdbool.h"

/* chapter 7: of RISC-V-SPEC-v2.2 

rs1: The address of the memory location (your lock variable, ptr).
rs2: The value to swap in (your new value, newval).
rd: The register where the original value will be stored (in this case, result).

%0 corresponds to result (the output).
%1 corresponds to *ptr (the memory address of the lock).
%2 corresponds to newval (the value to be swapped in).

*/
static inline int atomic_exchange(volatile int *ptr, int newval) {
    int result;
    asm volatile("amoswap.w %0, %2, %1"
                 : "=r"(result), "+A"(*ptr)
                 : "r"(newval)
                 : "memory");
    return result;
}

void mutex_init(mutex_t *mutex) {
    mutex->lock = 0;  // 0 means unlocked
}

void mutex_lock(mutex_t *mutex) {
    while (atomic_exchange(&mutex->lock, 1) != 0) {
        // Spin until the lock is acquired
    }
}

int mutex_trylock(mutex_t *mutex) {
    return atomic_exchange(&mutex->lock, 1) == 0;  // Return true if lock is acquired
}

void mutex_unlock(mutex_t *mutex) {
    mutex->lock = 0;  // Release the lock
}
