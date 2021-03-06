#ifndef __IDT_H
#define __IDT_H 1

#include "system.h"

#define INTERRUPT_FLAG 0x8E



/*
 * Fired whenever an inturrupt handler is called
 */
struct interrupt_event
{
	uint32_t gs, fs, es, ds; // pushed the last seg
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
	uint32_t int_no, err_code; // push byte #, our IDT table
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by processor automatically
};


typedef void (*interrupt_handler)(struct interrupt_event *event);


/** [ ASM ]
 * Initialize the IDT structure in assembly 
 */
extern void idt_load();

/**
 * Initialize the ISR and IDT data 
 */
void init_idt();

/**
 * Set an IDT gate
 * num   - IDT number
 * base  - Start of the IDT handler
 * sel   - The segment of the kernel
 * flags - The flags that need to be set for the CPU.
 *         Use the chart below to help set the flags
 *         |7| P |6| DPL |5||4| Always 01110 (14) |0|
 *         P - Segment is present? (1 = true)
 *         DPL - Ring this is in (0 to 3)
 */
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);

#endif