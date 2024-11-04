#pragma once

#include "core/core.h"
#include "libc/Wprintf.h"

#define PLIC_VIRT 0xc000000
#define UART0_VIRT 0x10000000


void Kernel_Trap_IRQ_HANDLER();
void TrapActivated();
void Kernel_Trap_IRQ_HANDLER();
void Start_PLIC();
int Irq_Id();
void Irq_served(int irqnumber);