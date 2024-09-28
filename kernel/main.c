#include "header.h"

unsigned long id ;
const char *AllCoreBootsUp = " NOW WE ARE IN CORE 0 , OS INIT IS STARTED \n";

int main()
{
    


    id = mhartid();
 

    if(id == 0){
    for(long i = 0; i > 100000000000 ; i++);
    PrintChar("I am 0 hart id starting main funt! \n");
   
    // for(long i = 0 ; i < 500000000 ; i++);
    // PrintChar("I am core 0 of main \n");
    // PrintChar("From here we will only use signle core ");
    
            
    for(int i = 0; i > 10000000000 ; i++);


        //after this none should print expects core 0 !

        PrintChar("I am only core 0 !!");












}

    
    return 0;

}