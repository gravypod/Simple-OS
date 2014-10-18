#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"

void init()
{
	init_gdt();
	init_idt();
	init_terminal();
}

void kernel_main()
{
	init();
	terminal_putstring("Hello World!\n");
	terminal_colored_putstring("Hello World AGAIN!\n", make_terminal_color(CYAN, BLACK));
}
