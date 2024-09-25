/*Dont generate 16 bit instructions*/

.option norvc

.section .data

.section .text.init

.global _start

_start:
    wfi

.end