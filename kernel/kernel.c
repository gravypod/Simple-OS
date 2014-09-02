#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"


void kernel_startup()
{
	init_terminal();
}

void kernel_main()
{
	kernel_startup();
	terminal_putstring("Hello World!\n");
	terminal_colored_putstring("Hello World AGAIN!\n", make_terminal_color(CYAN, BLACK));
}
