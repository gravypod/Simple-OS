#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"

void kernel_main()
{
	init_terminal();
	terminal_putstring("Hello World!\n");
	terminal_colored_putstring("Hello World AGAIN!\n", make_terminal_color(CYAN, BLACK));
}
