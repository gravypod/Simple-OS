
#ifndef __MEMORY_H
#define __MEMORY_H 1

#include "system.h"


/**
 * Page aligned address
 */
uint32_t kmalloc_a(uint32_t size);

/**
 * Returns a physical address
 */
uint32_t kmalloc_p(uint32_t size, uint32_t *physical);

/**
 * Page aligned physical address
 */
uint32_t kmalloc_ap(uint32_t size, uint32_t *physical);

/*
 * Standard memory allocation
 */
uint32_t kmalloc(uint32_t size);

#endif