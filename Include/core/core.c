#include "core.h"
#include "libc/Wprintf.h"
/*
  This fiel contains all the c functions associated with the core register 

*/
// Universal function to read a CSR register
unsigned long csr_read(const char* csr)
{
    unsigned long value;
    asm volatile("csrr %0, %1" : "=r" (value) : "i" (csr));
    return value;
}

// Universal function to write to a CSR register
void csr_write(const char* csr, unsigned long value)
{
    asm volatile("csrw %0, %1" : : "i" (csr), "r" (value));
}


unsigned long mhartid()
{
  unsigned long x;
  asm volatile("csrr %0, mhartid" : "=r" (x) );
  return x;
}
unsigned long 
r_tp()
{
  unsigned long x;
  asm volatile("mv %0, tp" : "=r" (x) );
  return x;
}

unsigned long mcause_read()
{
  unsigned long x;
  asm volatile("csrr %0, mcause" : "=r" (x) );
  return x;
}

unsigned long mstatus_read()
{
  unsigned long x;
  asm volatile("csrr %0, mstatus" : "=r" (x) );
  return x;
}


void mstatus_write( unsigned long x)
{
  asm volatile("csrw mstatus, %0" : : "r" (x));
}

unsigned long mtval_read()
{
  unsigned long x;
  asm volatile("csrr %0, mtval" : "=r" (x) );
  return x;
}
unsigned long get_mepc()
{
  unsigned long x;
  asm volatile("csrr %0, mepc" : "=r" (x) );
  return x;
}

void set_mepc(unsigned long x){
	asm volatile("csrw mepc, %0" : : "r" (x));
}

 void mret(){
	    asm volatile("mret");
}
unsigned char  get_mpp(void) {
    unsigned char mstatus = mstatus_read();
    return (mstatus >> 11) ;
  }

unsigned long misa_read(void) {
    unsigned long misa_value;
    asm volatile ("csrr %0, misa" : "=r" (misa_value));
    
    return misa_value;
}


void write_medeleg(unsigned long x){
  asm volatile("csrw medeleg , %0"  : :  "r" (x));
}
void write_mideleg(unsigned long x){
  asm volatile("csrw mideleg , %0"  : :  "r" (x));
}

unsigned long read_medeleg(){
  unsigned long x;
  asm volatile("csrr %0, medeleg" : "=r" (x) );
    return x;
}
unsigned long read_mideleg(){
  unsigned long x;
  asm volatile("csrr  %0, mideleg "  :  "=r" (x));
  return x;
}
void sie_write(unsigned long x )
{
  asm volatile("csrw sie, %0" : : "r" (x));
}

unsigned long sie_read(){
  unsigned long x;
  asm volatile("csrr %0, sie" : "=r" (x));
  return x;
}
void pmpcfg0_write(unsigned long  x)
{
  asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

void pmpaddr0_write(unsigned long  x)
{
  asm volatile("csrw pmpaddr0, %0" : : "r" (x));
}
unsigned long satp_read(){
  unsigned long x;
  asm volatile("csrr %0 , satp" : "=r" (x));
  return x;
}
void satp_write(unsigned long x){
  asm volatile("csrw satp , %0" : : "r" (x));
}
void sstatus_write(unsigned long x){
  asm volatile("csrw sstatus , %0" : : "r" (x));
}
inline unsigned long sstatus_read(){
  unsigned long x;
  asm volatile("csrr %0 ,sstatus" : "=r" (x));
  return x;
}
void write_sscratch(unsigned long value) {
  asm volatile("csrw sscratch, %0" : : "r"(value));
}
uint64_t mie_read()
{
  uint64_t x;
  asm volatile("csrr %0, mie" : "=r" (x) );
  return x;
}
void mie_write(uint64_t x)
{
  asm volatile("csrw mie, %0" : : "r" (x));
}
// Machine Environment Configuration Register
uint64_t menvcfg_read()
{
  uint64_t x;
  // asm volatile("csrr %0, menvcfg" : "=r" (x) );
  asm volatile("csrr %0, 0x30a" : "=r" (x) );
  return x;
}

void menvcfg_write(uint64_t x)
{
  // asm volatile("csrw menvcfg, %0" : : "r" (x));
  asm volatile("csrw 0x30a, %0" : : "r" (x));
}

// Machine-mode Counter-Enable
void mcounteren_write(uint64_t x)
{
  asm volatile("csrw mcounteren, %0" : : "r" (x));
}

uint64_t mcounteren_read()
{
  uint64_t x;
  asm volatile("csrr %0, mcounteren" : "=r" (x) );
  return x;
}
// Supervisor Timer Comparison Register
uint64_t stimecmp_read()
{
  uint64_t x;
  // asm volatile("csrr %0, stimecmp" : "=r" (x) );
  asm volatile("csrr %0, 0x14d" : "=r" (x) );
  return x;
}

void stimecmp_write(uint64_t x)
{
  // asm volatile("csrw stimecmp, %0" : : "r" (x));
  asm volatile("csrw 0x14d, %0" : : "r" (x));
}

// machine-mode cycle counter
uint64_t time_read()
{
  uint64_t x;
  asm volatile("csrr %0, time" : "=r" (x) );
  return x;
}

uint64_t tp_read()
{
  uint64_t x;
  asm volatile("mv %0, tp" : "=r" (x) );
  return x;
}

void tp_write(unsigned long hartid) {
    asm volatile("mv tp, %0" :: "r"(hartid));
}

void EnableInterrupt(){
  sstatus_write(sstatus_read() | (1UL << 1));
  //my_printf("Interupt enabled\n");
}
void DisableInterrupt(){

  sstatus_write(sstatus_read() & ~(1UL << 1));
  //my_printf("Interupt diabled\n");
}

