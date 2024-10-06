#include "start.h"
#include "../Include/mutex/mutex.h"
#include "../Include/core/core.h"

#define NCPU 4
const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";

unsigned long id ;
unsigned long var;
unsigned long getMPP;
unsigned long sieregister;

void timerinit();

// boot.S needs one stack per CPU.

__attribute__ ((aligned (16))) char stack0[4096 * NCPU];


void start(){
    

    var = mstatus_read();
    // MPP -> hold the previous priviliged mode bits :
    // https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf -> page 17
    // clear them 
    // PrintDigit(var);
    // getMPP = get_mpp();
    // PrintDigit(getMPP);

    // SET THE PREVIOUS STATE TO SUPERVISOR MODE , PUTTING FN OF MAIN INSIDE mepc SO WHEN WE RETURN 
    var &= ~(3UL << 11); // 11 -> machine mode
    var |=  (1UL << 11) ; // 01 -> supervisor mode
    mstatus_write(var);
    set_mepc((unsigned long)main());

    // mret return from machine mode and enteres in the previous mode and start executing in the supervisor mode 
    // so the main will run inside supervisor mode!!


    // We also dont wanted that someone will come as an exception and mess up our machine mode 
    // so we tried to handle int / exception and redirect it to S - Mode instead of M - Mode
    // If we set the bit all the bit of medeleg && mideleg we can redirect it to super visor mode
    // each bit of these registers corresponds to int / exe .

    write_medeleg(0xFFFF);
    write_mideleg(0xFFFF);
    sieregister = sie_read();
    sieregister |((1UL << 1) | (1UL << 5) | (1UL << 9)); // enable 3 int for s mode
    sie_write(sieregister |((1UL << 1) | (1UL << 5) | (1UL << 9)));

    // I also wanted to give OS access to whole memory and then implement pagin while in the supervisor mode
    //https://www.reddit.com/r/RISCV/comments/otna8o/getting_into_supervisor_mode_with_paging_disabled/
    pmpaddr0_write(0x3fffffffffffffull);
    pmpcfg0_write(0xf);
    
    // ask for clock interrupts.
    timerinit();

    
    // keep each CPU's hartid in its tp register, for cpuid().
    id = mhartid();
    tp_write(id);

    mret();

}

// ask each hart to generate timer interrupts.
void
timerinit()
{
  // enable supervisor-mode timer interrupts.
  mie_write(mie_read() | (1L << 5));
  
  // enable the sstc extension (i.e. stimecmp).
  menvcfg_write(menvcfg_read() | (1L << 63)); 
  
  // allow supervisor to use stimecmp and time.
  mcounteren_write(mcounteren_read() | 2);
  
  // ask for the very first timer interrupt.
  stimecmp_write(time_read() + 1000000);
}
