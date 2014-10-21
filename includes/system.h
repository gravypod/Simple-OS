#ifndef __SYSTEM_H
#define __SYSTEM_H 1

#define KERNEL_SEGMENT 0x8
#define GDT_SEGMENT    0x10

typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


typedef long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

typedef int (*callback_t)();


/**
 * Copy a section of memory
 */
unsigned char *memcpy(void *dest, const void *src, int count);

/**
 * Set a section of memory
 */
unsigned char *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

int strlen(const char* str);

/**
 * Read a byte from a port
 */
uint8_t read_byte(uint16_t port);

/**
 * Write a byte to a port
 */
void write_byte(uint16_t port, uint8_t data);

/**
 * Read a word from a port
 */
uint16_t read_word(uint16_t port);

/**
 * Write a word to a port
 */
void write_word(uint16_t port, uint16_t data);

/**
 * Hault the kernel forever!
 */
extern void hang();

/**
 * Run the "sti" instruction
 */
extern void enable_interrupts();

#endif
