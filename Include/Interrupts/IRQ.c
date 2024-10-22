#include "IRQ.h"


void kernelSwitch(){
    my_printf("kernerl switch \n");

    IRQ_HANDLER();
}
extern void kernelvec();
void SetupInterrupt()
{
    // stvec_write((unsigned long)(kernelvec));
     __asm__ volatile("csrw stvec, %0" : : "r"(&kernelvec));
}

void SetupPlic(){
    int id = mhartid();
    *(unsigned int*)PLIC_SENABLE(id) = (1 << 10);
    *(unsigned int*)PLIC_SPRIORITY(mhartid()) = 0;
}


int take_plic_interrpt(void)
{
  int irq = *(unsigned int*)PLIC_SCLAIM(mhartid());
  return irq;
}

void serve_interrupt(int irq)
{
  *(unsigned long *)PLIC_SCLAIM(mhartid()) = irq;
  my_printf("served");
}



void SaveCurrentContext(){
      __asm__ volatile (
        "addi sp, sp, -256\n"
        "sd ra, 0(sp)\n"
        "sd sp, 8(sp)\n"
        "sd gp, 16(sp)\n"
        "sd tp, 24(sp)\n"
        "sd t0, 32(sp)\n"
        "sd t1, 40(sp)\n"
        "sd t2, 48(sp)\n"
        "sd a0, 72(sp)\n"
        "sd a1, 80(sp)\n"
        "sd a2, 88(sp)\n"
        "sd a3, 96(sp)\n"
        "sd a4, 104(sp)\n"
        "sd a5, 112(sp)\n"
        "sd a6, 120(sp)\n"
        "sd a7, 128(sp)\n"
        "sd t3, 216(sp)\n"
        "sd t4, 224(sp)\n"
        "sd t5, 232(sp)\n"
        "sd t6, 240(sp)\n"
        );
}



void RestoreOldContext(){

      __asm__ volatile (
        "ld ra, 0(sp)\n"
        "ld sp, 8(sp)\n"
        "ld gp, 16(sp)\n"
        "ld t0, 32(sp)\n"
        "ld t1, 40(sp)\n"
        "ld t2, 48(sp)\n"
        "ld a0, 72(sp)\n"
        "ld a1, 80(sp)\n"
        "ld a2, 88(sp)\n"
        "ld a3, 96(sp)\n"
        "ld a4, 104(sp)\n"
        "ld a5, 112(sp)\n"
        "ld a6, 120(sp)\n"
        "ld a7, 128(sp)\n"
        "ld t3, 216(sp)\n"
        "ld t4, 224(sp)\n"
        "ld t5, 232(sp)\n"
        "ld t6, 240(sp)\n"
        "addi sp, sp, 256\n"
        "sret\n"
        );
}


void IRQ_HANDLER(){
    my_printf("interrrr called");
    __asm__ volatile("csrrc zero, sip, %0" : : "r"(1 << 1));

}