#pragma once


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

