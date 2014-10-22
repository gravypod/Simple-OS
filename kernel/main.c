#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "interrupts/idt.h"
#include "interrupts/isr.h"
#include "interrupts/irq.h"
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "memory/paging.h"


void kernel_main()
{

	init_terminal();
	init_gdt();
	init_idt();
    init_isr();
    init_irq();

	//init_paging(); TODO: Fix paging
    
    //terminal_putstring("Testing faults\n");

    //uint32_t *ptr = (uint32_t*) 0xA0000000;
    //uint32_t do_page_fault = *ptr;

    init_timer();
	init_keyboard();
    enable_interrupts();

}
