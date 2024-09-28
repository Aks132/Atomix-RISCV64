#include "header.h"

unsigned long id ;
const char *AllCoreBootsUp = " NOW WE ARE IN CORE 0 , OS INIT IS STARTED \n";

int main()
{
    


    id = mhartid();
 

    if(id == 0){
    for(long i = 0; i > 100000000 ; i++);
    PrintChar("I am 0 hart id starting main funt! \n");
   
    // for(long i = 0 ; i < 500000000 ; i++);
    // PrintChar("I am core 0 of main \n");
    // PrintChar("From here we will only use signle core ");
    
            
    for(int i = 0; i > 100000000 ; i++);


        //after this none should print expects core 0 !

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
    var &= ~(3UL << 11); // 11 -> machine mode
    var |=  (1UL << 11) ; // 01 -> supervisor mode

    mstatus_write(var);

    
    PrintChar("\n");

    unsigned long var1 = mstatus_read();

    PrintDigit(var1);
    PrintChar("\n");

    if(var1){
        PrintChar("CONGO BHAI YOU ARE IN SUPERVISOR MODE\n");
    }









}

    
    return 0;

}