#include "start.h"
#include "../Include/mutex.h"
const char * core0 = "I am core 0! \n";
const char * core1 = "I am core 1! \n";
const char * core2 = "I am core 2! \n";
const char * core3 = "I am core 3! \n";

mutex_t my_mutex;




void Start(){
    unsigned long id ;
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
        
    For now we are operating in machine mode , now we can switch this into supervisor mode!

   */

    unsigned long var = mstatus_read();
    // MPP -> hold the previous priviliged mode bits :
    // https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf -> page 17
    // clear them 
    PrintDigit(var);


    PrintChar("Going in supervisor mode\n");
    // SET THE PREVIOUS STATE TO SUPERVISOR MODE , PUTTING FN OF MAIN INSIDE mepc SO WHEN WE RETURN 
    var &= ~(3UL << 11); // 11 -> machine mode
    var |=  (1UL << 11) ; // 01 -> supervisor mode
    mstatus_write(var);
    set_mepc((unsigned long)main());
    var = mstatus_read();
    PrintDigit(var);
    Println();Println();Println();
    unsigned long getMPP = get_mpp();
    PrintDigit(getMPP);
    Println();Println();Println();
    // mret return from machine mode and enteres in the previous mode and start executing in the supervisor mode 
    // so the main will run inside supervisor mode!!
    for(int i = 0 ; i>1000000 ; i++);
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
