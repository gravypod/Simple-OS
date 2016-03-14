#pragma once
#include "system.h"

typedef struct {
	uint32_t next_address;
} memory_allocation_t;

typedef struct {
	uint32_t address;
	uint32_t size;
} page_t;

void* allocate(size_t size);
void free(void* address);
void init_memory();
