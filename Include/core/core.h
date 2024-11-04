#pragma once
// for refererence!!
// static const MemMapEntry virt_memmap[] = {
//     [VIRT_DEBUG] =        {        0x0,         0x100 },
//     [VIRT_MROM] =         {     0x1000,        0xf000 },
//     [VIRT_TEST] =         {   0x100000,        0x1000 },
//     [VIRT_RTC] =          {   0x101000,        0x1000 },
//     [VIRT_CLINT] =        {  0x2000000,       0x10000 },
//     [VIRT_ACLINT_SSWI] =  {  0x2F00000,        0x4000 },
//     [VIRT_PCIE_PIO] =     {  0x3000000,       0x10000 },
//     [VIRT_PLATFORM_BUS] = {  0x4000000,     0x2000000 },
//     [VIRT_PLIC] =         {  0xc000000, VIRT_PLIC_SIZE(VIRT_CPUS_MAX * 2) },
//     [VIRT_APLIC_M] =      {  0xc000000, APLIC_SIZE(VIRT_CPUS_MAX) },
//     [VIRT_APLIC_S] =      {  0xd000000, APLIC_SIZE(VIRT_CPUS_MAX) },
//     [VIRT_UART0] =        { 0x10000000,         0x100 },
//     [VIRT_VIRTIO] =       { 0x10001000,        0x1000 },
//     [VIRT_FW_CFG] =       { 0x10100000,          0x18 },
//     [VIRT_FLASH] =        { 0x20000000,     0x4000000 },
//     [VIRT_IMSIC_M] =      { 0x24000000, VIRT_IMSIC_MAX_SIZE },
//     [VIRT_IMSIC_S] =      { 0x28000000, VIRT_IMSIC_MAX_SIZE },
//     [VIRT_PCIE_ECAM] =    { 0x30000000,    0x10000000 },
//     [VIRT_PCIE_MMIO] =    { 0x40000000,    0x40000000 },
//     [VIRT_DRAM] =         { 0x80000000,           0x0 },
// };
#include "libc/types.h"
#define UNUSED(x) (void)(x)

extern int main();
unsigned long mhartid();
unsigned long mstatus_read();
void mstatus_write( unsigned long x);
void set_mepc(unsigned long x);
void mret();
unsigned char  get_mpp(void);
unsigned long misa_read(void);
void write_medeleg(unsigned long x); // for exception
void write_mideleg(unsigned long x); // for interrupts
unsigned long read_medeleg();
unsigned long read_mideleg();
void sie_write(unsigned long x );
unsigned long sie_read();
void pmpcfg0_write(unsigned long  x);
void pmpaddr0_write(unsigned long  x);
unsigned long satp_read();
void satp_write(unsigned long x);
void sstatus_write(unsigned long x);
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
// static inline  unsigned long sepc_read();
void stvec_write(unsigned long x);
unsigned long stvec_read();
unsigned long scause_read();
unsigned long stval_read();

static inline unsigned long sepc_read(){
  unsigned long x;
  asm volatile("csrr %0, sepc" : "=r" (x) );
  return x;
}

#define PAGE_SIZE 		  4096
#define MAX_VIRTUAL_ADDR ((1L << (38)))
#define TRAMPOLINE_COMMMON_REGION (MAX_VIRTUAL_ADDR - PAGE_SIZE)
#define KERNELEND 		  (BASEADDDRKERNEL + (128*1024*1024)) 
#define TRAPFRAME (TRAMPOLINE_COMMMON_REGION - PAGE_SIZE)