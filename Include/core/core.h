<<<<<<< HEAD
#pragma once
#include "libc/types.h"
#define UNUSED(x) (void)(x)
=======
#ifndef CORE_H
#define CORE_H
#include "libc/types.h"
#define UNUSED(x) (void)(x)

>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241



//extern int main();

unsigned long mhartid(void);

unsigned long mstatus_read(void);
void mstatus_write(unsigned long x);

void set_mepc(unsigned long x);
void mret(void);
unsigned char get_mpp(void);

unsigned long misa_read(void);

void write_medeleg(unsigned long x);
void write_mideleg(unsigned long x);

unsigned long read_medeleg(void);
unsigned long read_mideleg(void);

void sie_write(unsigned long x);
unsigned long sie_read(void);

void pmpcfg0_write(unsigned long x);
void pmpaddr0_write(unsigned long x);

unsigned long satp_read(void);
void satp_write(unsigned long x);

void sstatus_write(unsigned long x);
<<<<<<< HEAD
unsigned long sstatus_read();
void DisableInterrupt();
void EnableInterrupt();
void write_sscratch(unsigned long value);
uint64_t mie_read();
void mie_write(uint64_t x);
uint64_t menvcfg_read();
void menvcfg_write(uint64_t x);
void mcounteren_write(uint64_t x);
uint64_t mcounteren_read();
uint64_t stimecmp_read();
void stimecmp_write(uint64_t x);
uint64_t time_read();
uint64_t tp_read();
void tp_write(unsigned long hartid);

#define PAGE_SIZE 		  4096
#define MAX_VIRTUAL_ADDR ((1L << (38)))
#define TRAMPOLINE_COMMMON_REGION (MAX_VIRTUAL_ADDR - PAGE_SIZE)
#define KERNELEND 		  (BASEADDDRKERNEL + (128*1024*1024)) 
#define TRAPFRAME (TRAMPOLINE_COMMMON_REGION - PAGE_SIZE)
=======
uint64_t sstatus_read(void);

uint64_t mie_read(void);
void mie_write(uint64_t x);

uint64_t menvcfg_read(void);
void menvcfg_write(uint64_t x);

void mcounteren_write(uint64_t x);
uint64_t mcounteren_read(void);

uint64_t stimecmp_read(void);
void stimecmp_write(uint64_t x);

uint64_t time_read(void);

uint64_t tp_read(void);   //thread pointer 
void tp_write(unsigned long hartid);

void EnableInterrupt(void);
void DisableInterrupt(void);

#endif //CORE_H


>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
