#ifndef __PAGING_H
#define __PAGING_H 1

#include "system.h"
#include "interrupts/isr.h"
#include "interrupts/idt.h"

typedef struct page
{
	uint32_t present  : 1; // Current page in memory
	uint32_t rw       : 1; // Read only if clear, rw if set
	uint32_t user     : 1; // Supervisor if cleared
	uint32_t accessed : 1; // Has the page been accessed to since the last refresh?
	uint32_t dirty    : 1; // Has the page been written to since the last refresh?
	uint32_t unused   : 7; // Unused & preseved bits
	uint32_t frame    : 20; // Frame address (right shifted 12 bytes)
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	
	/**
	 * Pointers to the page_table_ts
	 */
	page_table_t *tables[1024];
	
	/**
	 * Array of poninters to the page_table_ts above with thier physical address
	 * Used for loading into CR3
	 */
	uint32_t physical_tables[1024];

	/**
	 * Real address of the page
	 */
	uint32_t physical_address;

} page_directory_t;

void init_paging();

void switch_page_directory(page_directory_t *dir);


/**
 * Get the a page_t
 * address - Address of the page
 * Make    - Should we make a new page if it does not exist? 1 == yes
 * dir     - The page_directory_t we are looking in.
 */
page_t *get_page(uint32_t address, int make, page_directory_t *dir);


void page_fault_handler(struct interrupt_event *event);

#endif