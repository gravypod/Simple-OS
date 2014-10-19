ENTRY(_start)
SECTIONS
{
  . = 0x10000;
  .text : {
    *(.multiboot)
    *(.text);
    *(.bootstrap_stack)
  }
  .data : {
    *(.data)
  }
  .bss : {
    *(.bss)
  }
}