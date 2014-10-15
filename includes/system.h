#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);

/**
 * Read a byte from a port
 */
unsigned char read_byte(unsigned short port);

/**
 * Write a byte to a port
 */
void write_byte(unsigned short port, unsigned char data);

/**
 * Read a word from a port
 */
unsigned short read_word(unsigned short port);

/**
 * Write a word to a port
 */
void write_word(unsigned short port, unsigned short data);
