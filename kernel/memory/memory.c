
#include "memory/memory.h"
#include "system.h"

/**
 * End address of the kernel!
 * Defined in our linker script!
 */
extern uint32_t end;

/**
 * Address to the end kernel
 */ 
uint32_t next_free_address = (uint32_t) &end; // Used in paging.c

uint32_t kmalloc_int(uint32_t size, int align, uint32_t *physical)
{
	if (align == 1 && (next_free_address & 0xFFFFF000))
	{
		next_free_address &= 0xFFFFF000;
		next_free_address += 0x1000;
	}

	if (physical) // Check if we need to send back out internel address
	{
		*physical = next_free_address;
	}
	uint32_t start_address = next_free_address; // Bookmark the "start" of our kernel
	next_free_address += size; // Increment to the next free place
	return start_address; // Return our bookmark
}

uint32_t kmalloc_a(uint32_t size)
{
	return kmalloc_int(size, 1, 0);
}

uint32_t kmalloc_p(uint32_t size, uint32_t *physical)
{
	return kmalloc_int(size, 0, physical);
}

uint32_t kmalloc_ap(uint32_t size, uint32_t *physical)
{
	return kmalloc_int(size, 1, physical);
}

uint32_t kmalloc(uint32_t size)
{
	return kmalloc_int(size, 0, 0);
}