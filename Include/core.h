#pragma once


extern int main();
unsigned long mhartid();
unsigned long mstatus_read();
void mstatus_write( unsigned long x);
void set_mepc(unsigned long x);
void mret();
unsigned char  get_mpp(void);
unsigned long misa_read(void);


