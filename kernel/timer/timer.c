#include "interrupts/idt.h"
#include "interrupts/irq.h"
#include "terminal.h"
#include "system.h"

#define CPU_FREQUENCY 1193180
#define CPU_HZ        100

int ticks = 0;

void set_frequency(int hz)
{
	int divisor = CPU_FREQUENCY / hz;
	write_byte(0x43, 0x36);
	write_byte(0x40, divisor & 0xFF);
	write_byte(0x40, divisor >> 8);
}

void time_handler(struct interrupt_event *event)
{
	ticks++; // TODO: Handle processes
}

void init_timer()
{
	set_frequency(CPU_HZ); 
	irq_install(0, time_handler);
}