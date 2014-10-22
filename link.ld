ENTRY(_start)
SECTIONS
{
  . = 0x10000;
  .text : {
    *(.multiboot)
    *(.text);
    *(.rodata)
    *(.bootstrap_stack)
  }
  .data : {
    *(.data)
  }
  .bss : {
    *(.bss)
  }
  end = .;
}