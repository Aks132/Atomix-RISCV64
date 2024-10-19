// This is just a synchronous intreuption ><
#include "trap.h"


// Remember these are just for user trap we have to serve kernel interrup also 
// i may setup some other kernel trap funt later  , but for now leave it !!
void TrapCallfromUser(){

    if(sstatus_read() & (1<<8)){
        my_printf("user traped called from user mode !1 \n");
    }
}