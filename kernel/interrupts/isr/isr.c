#include "system.h"
#include "interrupts/isr.h"
#include "interrupts/isr_routines.h"
#include "interrupts/idt.h"
#include "terminal.h"

interrupt_handler handlers[32] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char *error_messages[] = 
{
	"Division By Zero Exception",
	"Debug Exception",
	"Non Maskable Interrupt Exception",
	"Breakpoint Exception",
	"Into Detected Overflow Exception",
	"Out of Bounds Exception",
	"Invalid Opcode Exception",
	"No Coprocessor Exception",
	"Double Fault Exception",
	"Coprocessor Segment Overrun Exception",
	"Bad TSS Exception",
	"Segment Not Present Exception",
	"Stack Fault Exception",
	"General Protection Fault Exception",
	"Page Fault Exception",
	"Unknown Interrupt Exception",
	"Coprocessor Fault Exception",
	"Alignment Check Exception (486+)",
	"Machine Check Exception (Pentium/586+)",
	"Reserved Exceptions", // 19 - 31
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions",
	"Reserved Exceptions"
};

void isr_handler(struct interrupt_event *error)
{
	if (error->int_no > 32)
	{
		return;
	}


	interrupt_handler handler = handlers[error->int_no];

	if (handler != 0)
	{
		handler(error);
	}

	terminal_putstring(error_messages[error->int_no]);
	terminal_putstring(" Thrown!\n");
	hang();
} 

void isr_register(uint8_t num, uint64_t base) 
{
	idt_set_gate(num, base, KERNEL_SEGMENT, INTERRUPT_FLAG);
}

void isr_install(uint8_t num, interrupt_handler handler)
{
	handlers[num] = handler;
}

void isr_uninstall(uint8_t num)
{
	handlers[num] = 0;
}

void init_isr()
{
	isr_register(0,  (unsigned) isr_0);
	isr_register(1,  (unsigned) isr_1);
	isr_register(2,  (unsigned) isr_2);
	isr_register(3,  (unsigned) isr_3);
	isr_register(4,  (unsigned) isr_4);
	isr_register(5,  (unsigned) isr_5);
	isr_register(6,  (unsigned) isr_6);
	isr_register(7,  (unsigned) isr_7);
	isr_register(8,  (unsigned) isr_8);
	isr_register(9,  (unsigned) isr_9);
	isr_register(10, (unsigned) isr_10);
	isr_register(11, (unsigned) isr_11);
	isr_register(12, (unsigned) isr_12);
	isr_register(13, (unsigned) isr_13);
	isr_register(14, (unsigned) isr_14);
	isr_register(15, (unsigned) isr_15);
	isr_register(16, (unsigned) isr_16);
	isr_register(17, (unsigned) isr_17);
	isr_register(18, (unsigned) isr_18);
	isr_register(19, (unsigned) isr_19);
	isr_register(20, (unsigned) isr_20);
	isr_register(21, (unsigned) isr_21);
	isr_register(22, (unsigned) isr_22);
	isr_register(23, (unsigned) isr_23);
	isr_register(24, (unsigned) isr_24);
	isr_register(25, (unsigned) isr_25);
	isr_register(26, (unsigned) isr_26);
	isr_register(27, (unsigned) isr_27);
	isr_register(28, (unsigned) isr_28);
	isr_register(29, (unsigned) isr_29);
	isr_register(30, (unsigned) isr_30);
	isr_register(31, (unsigned) isr_31);
}