OUTPUT_ARCH("riscv")

ENTRY(_entry)


MEMORY
{
  ram  (wxa) : ORIGIN = 0x80000000, LENGTH = 128M
}

/*
    Only wanted to create these section which are mentioned in PHDRS
*/

PHDRS
{
    text PT_LOAD;
    data PT_LOAD;
    bss PT_LOAD;
    stack PT_LOAD;
}
/*
    no need to do copy from phymem to vma , in qemu we can bypass that 
    which decrease copying overhead 
*/
SECTIONS
{
   . = 0x80000000;
  .text : {
    PROVIDE(_text_start = .);
    *(*)
    PROVIDE(_text_end = .);
  } >ram AT>ram :text

   PROVIDE(_global_pointer = .);

  .rodata : {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  } >ram AT>ram :text

  .data : {
    . = ALIGN(4096);
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*) *(.data .data.*)
    PROVIDE(_data_end = .);
  } >ram AT>ram :data

  .bss : {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) *(.bss .bss.*)
    PROVIDE(_bss_end = .);
  } >ram AT>ram :bss
 
  .stack : {
    PROVIDE(_stack_start = .);
    . = . + 4096*4;
    PROVIDE(_stack_end = .);
  } >ram AT>ram :stack 
  PROVIDE(_end_ = .);
}
    
    PROVIDE(_memory_start = ORIGIN(ram));
