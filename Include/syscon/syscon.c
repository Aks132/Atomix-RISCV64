#ifndef __SYSCON_H__
#define __SYSCON_H__
#include "libc/types.h"
#include "syscon/syscon.h"
#include "uart/uart.h"

void poweroff(void) {
  UART_SEND("Poweroff requested");
  *(uint32_t *)SYSCON_ADDR = 0x5555;
}

void reboot(void) {
  UART_SEND("Reboot requested");
  *(uint32_t *)SYSCON_ADDR = 0x7777;
}

#endif //__SYSCON_H__

