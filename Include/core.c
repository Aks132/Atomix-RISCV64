#include <core.h>

unsigned long mhartid()
{
  unsigned long x;
  asm volatile("csrr %0, mhartid" : "=r" (x) );
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


