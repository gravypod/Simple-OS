
//TODO: Port this into the kernel_entry.asm file
// This should all be extern
unsigned char read_byte(unsigned short port)
{
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void write_byte(unsigned short port, unsigned char data)
{
	__asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

unsigned short read_word(unsigned short port)
{
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void write_word(unsigned short port, unsigned short data)
{
	__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}
