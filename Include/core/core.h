#pragma once

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


#define PAGE_SIZE 		  4096
#define MAX_VIRTUAL_ADDR ((1L << (38)))
#define TRAMPOLINE_COMMMON_REGION (MAX_VIRTUAL_ADDR - PAGE_SIZE)
#define KERNELEND 		  (BASEADDDRKERNEL + (128*1024*1024)) 
#define TRAPFRAME (TRAMPOLINE_COMMMON_REGION - PAGE_SIZE)