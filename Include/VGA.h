#pragma once
#include "../Include/libc/Wprintf.h"
#include "../Include/libc/bool.h"
#define MODE_13_REGS_SIZE 28
#define PALETTE_SIZE 256
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
void set_mode13();
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void makeWhite();
void makeBlack();
void H();
void E();
void L1();
void L2();
void O();
void Exclamation1();
void Exclamation2();
