#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "interrupts/idt.h"

void kernel_main()
{
	init_gdt();
	init_terminal();
	init_idt();
	
    __asm__ __volatile__ ("sti");

	hang(); // Hang the system!
}
