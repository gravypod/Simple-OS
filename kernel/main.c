#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "interrupts/idt.h"
#include "interrupts/isr.h"
#include "interrupts/irq.h"
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "memory/memory.h"

void kernel_main()
{

	init_terminal();

	terminal_putstring("Building GDT\n");
	init_gdt();

	terminal_putstring("Loading Interrupts\n");
	init_idt();
	init_isr();
	init_irq();

	uint32_t number = 102;
	terminal_putstring("Printing 102: ");
	terminal_putdec(number);
	terminal_putstring("\n");

	terminal_putstring("Initializing timer\n");
	init_timer();

	terminal_putstring("Initializing Interrupts\n");
	init_keyboard();
	enable_interrupts();
}
