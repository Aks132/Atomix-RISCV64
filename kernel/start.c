#include "start.h"
#include "../Include/mutex.h"
#include "../Include/core.h"
const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";

mutex_t my_mutex;
unsigned long id ;
unsigned long var;
unsigned long getMPP;
unsigned long sieregister;


void Start(){
    id = mhartid();
    if(id == 0)
    {
    for(long i = 0; i > 100000000 ; i++);
    PrintChar("I am 0 hart id starting main funt! \n");
    // for(long i = 0 ; i < 500000000 ; i++);
    // PrintChar("I am core 0 of main \n");
    // PrintChar("From here we will only use signle core ");
    for(int i = 0; i > 100000000 ; i++);
        //after this none should print expects core 0 
    PrintChar("I am only core 0 !!");

   PrintChar("\n");PrintChar("\n");PrintChar("\n");PrintChar("\n");PrintChar("\n");

   /*

    Check for misa register :) 

   */


    unsigned long misa = misa_read();
    unsigned long base_isa = misa & 0x3; 

    switch(base_isa) {
        case 0: PrintChar("Base ISA: RV32\n"); break;
        case 1: PrintChar("Base ISA: RV64\n"); break;
        case 2: PrintChar("Base ISA: RV128\n"); break;
        default: PrintChar("Unknown base ISA\n"); break;
    }// finally some use of switch case LOL
    

    PrintChar("Supported Extensions:\n");

    if (misa & (1UL << ('I' - 'A'))) PrintChar("  Extension: 'I' (Integer)\n");
    if (misa & (1UL << ('M' - 'A'))) PrintChar("  Extension: 'M' (Multiply/Divide)\n");
    if (misa & (1UL << ('A' - 'A'))) PrintChar("  Extension: 'A' (Atomic)\n");
    if (misa & (1UL << ('F' - 'A'))) PrintChar("  Extension: 'F' (Single-Precision Floating Point)\n");
    if (misa & (1UL << ('D' - 'A'))) PrintChar("  Extension: 'D' (Double-Precision Floating Point)\n");
    if (misa & (1UL << ('C' - 'A'))) PrintChar("  Extension: 'C' (Compressed Instructions)\n");
    if (misa & (1UL << ('S' - 'A'))) PrintChar("  Extension: 'S' (Supervisor Mode)\n");
    if (misa & (1UL << ('U' - 'A'))) PrintChar("  Extension: 'U' (User Mode)\n");
    if (misa & (1UL << ('Q' - 'A'))) PrintChar("  Extension: 'Q' (Quad-Precision Floating Point)\n");
    if (misa & (1UL << ('V' - 'A'))) PrintChar("  Extension: 'V' (Vector Operations)\n");
    if (misa & (1UL << ('B' - 'A'))) PrintChar("  Extension: 'B' (Bit Manipulation)\n");
    if (misa & (1UL << ('P' - 'A'))) PrintChar("  Extension: 'P' (Packed-SIMD)\n");
    if (misa & (1UL << ('H' - 'A'))) PrintChar("  Extension: 'H' (Hypervisor)\n");
    if (misa & (1UL << ('E' - 'A'))) PrintChar("  Extension: 'E' (Embedded Base Integer ISA)\n");
    if (misa & (1UL << ('J' - 'A'))) PrintChar("  Extension: 'J' (Dynamic Translations)\n");
    if (misa & (1UL << ('T' - 'A'))) PrintChar("  Extension: 'T' (Transaction Memory)\n");
    if (misa & (1UL << ('L' - 'A'))) PrintChar("  Extension: 'L' (Decimal Floating Point)\n");
    if (misa & (1UL << ('N' - 'A'))) PrintChar("  Extension: 'N' (User-level interrupts)\n");
    if (misa & (1UL << ('X' - 'A'))) PrintChar("  Extension: 'X' (Non-standard extensions)\n");
    if (misa & (1UL << ('Z' - 'A'))) PrintChar("  Extension: 'Z' (Standard extensions)\n");

        /*
    For now we are operating in machine mode , now we can switch this into supervisor mode!

   */

    var = mstatus_read();
    // MPP -> hold the previous priviliged mode bits :
    // https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf -> page 17
    // clear them 
    // PrintDigit(var);
    // getMPP = get_mpp();
    // PrintDigit(getMPP);
    Println();Println();Println();






    // SET THE PREVIOUS STATE TO SUPERVISOR MODE , PUTTING FN OF MAIN INSIDE mepc SO WHEN WE RETURN 
    var &= ~(3UL << 11); // 11 -> machine mode
    var |=  (1UL << 11) ; // 01 -> supervisor mode
    mstatus_write(var);
    set_mepc((unsigned long)main());

    Println();Println();Println();
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
    mret();


}
}

void Core0_Init(){
    mutex_lock(&my_mutex);
    Println();
    PrintChar(core0);
    Println();
    mutex_unlock(&my_mutex);
    Start();
}

void Core1_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core1);
    Println();
    mutex_unlock(&my_mutex);
    // main();
}

void Core2_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core2);
    Println();
    mutex_unlock(&my_mutex);
    // main();
}

void Core3_Init(){
    mutex_lock(&my_mutex);

    Println();
    PrintChar(core3);
    Println();
    mutex_unlock(&my_mutex);
    // main();
}
