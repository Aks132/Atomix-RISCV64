// This is just a synchronous intreuption ><
#include "trap.h"

void m_trap();

void m_trap() {
    // Async trap are those which happen due to other process on current on going intruction,
    // sync one happens durring current execution
    int hart = mhartid();
    uint64_t status = mstatus_read();
    uint64_t cause = mcause_read();
    uint64_t epc = get_mepc();
    uint64_t tval = mtval_read();

    int is_async = (cause >> 63) & 1;
    int cause_num = cause & 0xfff;
    uint64_t return_pc = epc;

    if (is_async) {
        // Asynchronous trap
        switch (cause_num) {
            case 3:
                my_printf("Machine software interrupt CPU#%lu\n", hart);
                break;
            case 7:
                // Machine timer
                //*(volatile uint64_t *)MMIO_MTIMECMP = *(volatile uint64_t *)MMIO_MTIME + 10000000;
                break;
            case 11:
                my_printf("Machine external interrupt CPU#%d\n", hart);
                break;
            default:
                my_printf("Unhandled async trap CPU#%d -> %d\n", hart, cause_num);
                break;
        }
    } else {
        // Synchronous trap
        switch (cause_num) {
            case 2:
                my_printf("Illegal instruction CPU#%lu -> 0x%x: 0x%x\n", hart, epc, tval);
                // Handle illegal instruction
                break;
            case 8:
                my_printf("E-call from User mode! CPU#%d -> 0x%x\n", hart, epc);
                return_pc += 4;
                break;
            case 9:
                my_printf("E-call from Supervisor mode! CPU#%d -> 0x%x\n", hart, epc);
                return_pc += 4;
                break;
            case 11:
                my_printf("E-call from Machine mode! CPU#%d -> 0x%x\n", hart, epc);
                break;
            case 12:
                my_printf("Instruction page fault CPU#%d -> 0x%x: 0x%x\n", hart, epc, tval);
                return_pc += 4;
                break;
            case 13:
                my_printf("Load page fault CPU#%d -> 0x%x: 0x%x\n", hart, epc, tval);
                return_pc += 4;
                break;
            case 15:
                my_printf("Store page fault CPU#%d -> 0x%x: 0x%x\n", hart, epc, tval);
                return_pc += 4;
                break;
            default:
                my_printf("Unhandled sync trap CPU#%d -> 0x%x: 0x%x\n", hart, epc, tval);
                
                break;
        }
    }

    // Return updated program counter
    //return return_pc;

}