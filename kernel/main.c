#include "header.h"

unsigned long id ;
const char *AllCoreBootsUp = " NOW WE ARE IN CORE 0 , OS INIT IS STARTED \n";

int main()
{
    

    Println();
    Println();
    Println();
    Println();
    Println();
    Println();
    Println();
    Println();
    Println();
    Println();

    id = mhartid();
    if(id == 0)
    {
    PrintChar(core0);
    }
    id = mhartid();
    if(id == 1)
    {
    PrintChar(core1);
    }
    

    
    return 0;

}