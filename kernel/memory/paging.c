#include "system.h"
#include "memory/paging.h"
#include "memory/memory.h"
#include "interrupts/isr.h"
#include "interrupts/idt.h"
#include "terminal.h"

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

#define FRAME_FULL   0xFFFFFFFF
#define MEMORY_CHUNK 0x1000
#define MEMORY_END   0x1000000

extern uint32_t next_free_address; // Declared in memory.c

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

uint32_t *frames;
uint32_t nframes;

static uint32_t get_frame_addr(uint32_t address)
{
	return address / MEMORY_CHUNK;
}

// Set a bit in the frames bitset
static void set_frame(uint32_t address)
{
	uint32_t frame = get_frame_addr(address);
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);
	frames[index] &= ~(0x1 << offset);
}

static void clear_frame(uint32_t address)
{
	uint32_t frame = get_frame_addr(address);
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);
	frames[index] |= (0x1 << offset);
}

static uint32_t test_frame(uint32_t address)
{
	uint32_t frame = get_frame_addr(address);
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);
	return frames[index] & (0x1 << offset);	
}

static uint32_t get_next_free()
{
	for (uint32_t i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		if (frames[i] == FRAME_FULL) // Frame is currently full
		{
			continue;
		}

		for (uint32_t offset = 0; offset < 32; offset++)
		{
			if (frames[i] & (0x1 << offset)) // Frame is not free
			{
				continue;
			}
			// Index * real size + offset
			return i * 4 * 8 + offset;
		}
	}

	return (uint32_t) -1; // Error signal
}

void frame_alloc(page_t *page, int is_kernel, int is_writable)
{
	if (page->frame != 0)
	{
		return;
	}

	uint32_t index = get_next_free();
	if (index == (uint32_t) -1)
	{
		terminal_putstring("NO FREE MEM");
		return;
		// TODO: Panic, no free memory!?!?!
	}

	set_frame(index * MEMORY_CHUNK);
	page->present = 1; // Used? Hell yea!
	page->rw = is_writable ? 1 : 0; // Writable? Yea!
	page->user = is_kernel ? 0 : 1; // Kernel?
	page->frame = index;
}

void frame_free(page_t *page)
{
	uint32_t frame;

	if (!(frame = page->frame))
	{
		return;
	}

	clear_frame(frame); // Clear the frame
	page->frame = 0x0; // This page has no frame!
}

void init_paging()
{
	nframes = MEMORY_END / MEMORY_CHUNK;


	frames = (uint32_t*) kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	kernel_directory = (page_directory_t*) kmalloc_a(sizeof(page_directory_t));
	current_directory = kernel_directory;

	int kernelIndex = 0;

	while (kernelIndex < next_free_address)
	{
		frame_alloc(get_page(kernelIndex, 1, kernel_directory), 0, 0);
		kernelIndex += MEMORY_CHUNK;
	}

	//isr_install(14, page_fault_handler);

	switch_page_directory(kernel_directory);

}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	__asm__ __volatile__("mov %0, %%cr3":: "r"(&dir->physical_tables));
	uint32_t cr0;
	__asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	__asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));

}

page_t *get_page(uint32_t address, int make, page_directory_t *dir)
{
	address /= MEMORY_CHUNK;
	uint32_t index = address / 1024;

	if (dir->tables[index])
	{
		return &dir->tables[index]->pages[address % 1024];
	} 
	else if(make)
	{
		uint32_t physical_location;
		dir->tables[index] = (page_table_t*) kmalloc_ap(sizeof(page_table_t), &physical_location);
		memset(dir->tables[index], 0, MEMORY_CHUNK);
		dir->physical_tables[index] = physical_location | 0x7; // Present RW and user
		return &dir->tables[index]->pages[address % 1024];
	}
	else
	{
		return 0;
	}
}

void page_fault_handler(struct interrupt_event *event)
{
	// TODO: Implement handler!
	terminal_putstring("Error paging!");
}