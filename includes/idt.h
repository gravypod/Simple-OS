#ifndef __IDT_H
#define __IDT_H 1

/** [ ASM ]
 * Initialize the IDT structure in assembly 
 */
extern void idt_load();

/**
 * Initialize the ISR and IDT data 
 */
void init_idt();

#endif