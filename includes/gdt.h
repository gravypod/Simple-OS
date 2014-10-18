#ifndef __GDT_H
#define __GDT_H 1

/**
 * Initiallize the GDT
 * (Allows us to setup memory allocations)
 */ 
void init_gdt();

/** [ ASM ]
 * Flush the GDT into memory
 */
extern void gdt_flush();

#endif