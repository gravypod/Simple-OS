#include "interrupts/irq.h"
#include "interrupts/idt.h"
#include "interrupts/irq_routines.h"
#include "timer/timer.h"
#include "system.h"
#include "terminal.h"

interrupt_handler irqs[16] =
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};

void irq_install(int irq, interrupt_handler handler)
{
	irqs[irq] = handler;
}

void irq_uninstall(int irq)
{
	irqs[irq] = 0;
}

void irq_remap()
{
	write_byte(0x20, 0x11);
	write_byte(0xA0, 0x11);
	write_byte(0x21, 0x20);
	write_byte(0xA1, 0x28);
	write_byte(0x21, 0x04);
	write_byte(0xA1, 0x02);
	write_byte(0x21, 0x01);
	write_byte(0xA1, 0x01);
	write_byte(0x21, 0x0);
	write_byte(0xA1, 0x0);
}

void irq_register(uint8_t num, uint64_t base)
{
	idt_set_gate(num, base, KERNEL_SEGMENT, INTERRUPT_FLAG);
}

void init_irq()
{
	irq_remap();

	irq_register(32, (unsigned) irq_0);
	irq_register(33, (unsigned) irq_1);
	irq_register(34, (unsigned) irq_2);
	irq_register(35, (unsigned) irq_3);
	irq_register(36, (unsigned) irq_4);
	irq_register(37, (unsigned) irq_5);
	irq_register(38, (unsigned) irq_6);
	irq_register(39, (unsigned) irq_7);
	irq_register(40, (unsigned) irq_8);
	irq_register(41, (unsigned) irq_9);
	irq_register(42, (unsigned) irq_10);
	irq_register(43, (unsigned) irq_11);
	irq_register(44, (unsigned) irq_12);
	irq_register(45, (unsigned) irq_13);
	irq_register(46, (unsigned) irq_14);
	irq_register(47, (unsigned) irq_15);
	
}

interrupt_handler irq_get_handler(int irq)
{
	return irqs[irq];
}

void irq_handler(struct interrupt_event *event)
{
	interrupt_handler handler = irq_get_handler(event->int_no - 32);

	if (handler != 0)
	{
		handler(event);
	}

	if (event->int_no >= 40) // This was an IRQ8 to IRQ14
	{
		write_byte(0xA0, 0x20); // Send EOI to slave controller
	}

	write_byte(0x20, 0x20); // Send EOI to master controller
}