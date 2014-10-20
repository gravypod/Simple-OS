#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "interrupts/idt.h"
#include "interrupts/isr.h"
#include "interrupts/irq.h"
#include "timer/timer.h"
#include "keyboard/keyboard.h"


void kernel_main()
{
	init_terminal();
	init_gdt();
	init_idt();
    init_isr();
    init_irq();
    init_timer();
	init_keyboard();

    enable_interupts();

}
