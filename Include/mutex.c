#include "mutex.h"
#include "../Include/libc/bool.h"
#include "../Include/core.h"

/* chapter 7: of RISC-V-SPEC-v2.2 

rs1: The address of the memory location (your lock variable, ptr).
rs2: The value to swap in (your new value, newval).
rd: The register where the original value will be stored (in this case, result).

%0 corresponds to result (the output).
%1 corresponds to *ptr (the memory address of the lock).
%2 corresponds to newval (the value to be swapped in).

link : https://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Atomic-Builtins.html


RISC-V atomic swap using amoswap.w instruction */
static inline int atomic_exchange(volatile int *ptr, int newval) {
    int result;
    asm volatile("amoswap.w %0, %2, %1"
                 : "=r"(result), "+A"(*ptr)
                 : "r"(newval)
                 : "memory");
    return result;
}

/* Initialize the mutex */
void mutex_init(mutex_t *mutex, char* name) {
    mutex->lock = 0;  // 0 means unlocked
    mutex->name = name;
}

/* Acquire the mutex lock */
void mutex_lock(mutex_t *mutex) {
    DisableInterrupt();  // Disable interrupts before entering critical section
    while (atomic_exchange(&mutex->lock, 1) != 0) {
        // Spin-wait until we acquire the lock
        // Optionally, add a small pause here to reduce CPU load
        // asm volatile ("pause");  // x86 example, you can find a suitable RISC-V pause instruction if needed
    }
    __sync_synchronize();  // Memory barrier to ensure lock is properly acquired
    EnableInterrupt();  // Re-enable interrupts after acquiring the lock
}

/* Try to acquire the mutex lock without blocking */
int mutex_trylock(mutex_t *mutex) {
    DisableInterrupt();
    int result = atomic_exchange(&mutex->lock, 1) == 0;  // Return true if lock is acquired
    EnableInterrupt();
    return result;
}

/* Release the mutex lock */
void mutex_unlock(mutex_t *mutex) {
    DisableInterrupt();  // Disable interrupts before releasing the lock
    __sync_synchronize();  // Memory barrier before releasing the lock
    atomic_exchange(&mutex->lock, 0);  // Atomically release the lock
    EnableInterrupt();  // Re-enable interrupts after releasing the lock
}
