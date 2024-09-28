#include "header.h"




int main()
{
    
    PrintChar("We are in  supervisor mode\n");
    unsigned char mpp = get_mpp(); // this value is giving 0 ( but i am not sure it should give an erro or not)
    PrintChar("Now ig we cant access mpp\n"); // because it is showing 0 !!


}