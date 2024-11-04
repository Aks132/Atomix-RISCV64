#include "IRQ.h"

extern void SaveCurrentContext();
extern void KernelVectorSwitch();

void TrapActivated()
{
  stvec_write((unsigned long) KernelVectorSwitch & ~0x3);
}

void Kernel_Trap_IRQ_HANDLER()
{
  // supervisor sanity check!!
  if((sstatus_read() & (1L << 8)) == 0){ my_printf("kerneltrap: not from supervisor mode"); }
  
}

void Start_PLIC(){
  *(unsigned int*)(PLIC_VIRT + UART0_VIRT*4) = 1;
  *(unsigned int*)(PLIC_VIRT + 0x2080) = (1 << 10);
  *(unsigned int*)((PLIC_VIRT + 0x201000 )) = 0;  // we are making it 0 , so irq with '1' will come as prio.
}

inline int Irq_Id(){
  return *(unsigned int *)(PLIC_VIRT + 0x201004);
}
inline void Irq_served(int irqnumber){
  *(unsigned int *)(PLIC_VIRT + 0x201004) = irqnumber;
}
