
#include "terminal.h"
#include "system.h"

void init_terminal()
{
	terminal.row = 0; // Start at top left
	terminal.column = 0;
	terminal.buffer = (uint16_t*) VIDEO_MEMORY_LOCATION;
	terminal.color = make_terminal_color(WHITE, BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			terminal.buffer[get_screen_index(x, y)] = make_vga_entry(' ');
		}
	}

}

uint16_t make_colored_vga_entry(char c, unsigned char color)
{
	return ((uint16_t)c) | ((uint16_t) color) << 8;
}

uint16_t make_vga_entry(char c)
{
	return make_colored_vga_entry(c, terminal.color);
}

size_t get_screen_index(size_t column, size_t row)
{
	const size_t index = row * VGA_WIDTH + column;
	return index;
}

size_t get_current_screen_index()
{
	return get_screen_index(terminal.column, terminal.row);
}

unsigned char make_terminal_color(enum terminal_color fg, enum terminal_color bg)
{
	return fg | bg << 4;
}

void terminal_colored_putchar(char c, unsigned char color)
{

	if (c == '\n')
	{
		++terminal.row;
		terminal.column = 0;
		return;
	}

	terminal.buffer[get_current_screen_index()] = make_colored_vga_entry(c, color);

	if (++terminal.column == VGA_WIDTH)
	{
		terminal.column = 0;
		if (++terminal.row == VGA_HEIGHT)
		{
			terminal.row = 0;
		}
	}

}

void terminal_colored_putstring(const char* data, unsigned char color)
{
	for (size_t i = 0; i < strlen(data); i++)
	{
		terminal_colored_putchar(data[i], color);
	}
}

void terminal_putchar(char c)
{
	terminal_colored_putchar(c, terminal.color);
}

void terminal_putstring(const char* data)
{
	terminal_colored_putstring(data, terminal.color);
}

