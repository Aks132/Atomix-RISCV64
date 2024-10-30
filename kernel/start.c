#include "start.h"


void Start() {
    unsigned long var;
    var = mstatus_read();
    var &= ~(3UL << 11); // 11 -> machine mode
    var |= (1UL << 11);  // 01 -> supervisor mode
    mstatus_write(var);
    set_mepc((unsigned long)main());
    satp_write(0x00);
    write_medeleg(0xFFFF);
    write_mideleg(0xFFFF);
    sie_write(sie_read() | ((1UL << 1) | (1UL << 5) | (1UL << 9)));
    pmpaddr0_write(0x3fffffffffffffull);
    pmpcfg0_write(0xf);
    mie_write(mie_read() | (1L << 5)); 
    mret();
}

void Core0_Init() 
{
    Start();
}

void Core1_Init() {}

void Core2_Init() {}

void Core3_Init() {}