#ifndef CORE_H
#define CORE_H
#include "libc/types.h"
#define UNUSED(x) (void)(x)




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


