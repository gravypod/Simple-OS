#ifndef __IDT_H
#define __IDT_H 1

#include "system.h"

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