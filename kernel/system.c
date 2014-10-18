#include "system.h"


unsigned char *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

unsigned char *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char* str)
{
	int ret;
	for (ret = 0; str[ret] != 0; ret++);
	return ret;
}

//TODO: Port this into the kernel_entry.asm file
// This should all be extern
uint8_t read_byte(uint16_t port)
{
	uint8_t result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void write_byte(uint16_t port, uint8_t data)
{
	__asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

uint16_t read_word(uint16_t port)
{
	uint16_t result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void write_word(uint16_t port, uint16_t data)
{
	__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}
