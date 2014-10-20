
#include "terminal.h"
#include "system.h"

void init_terminal()
{
	terminal.row = 0; // Start at top left
	terminal.column = 0;
	terminal.buffer = (uint16_t*) VIDEO_MEMORY_LOCATION;
	terminal.color = make_terminal_color(WHITE, BLACK);

	for (uint8_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (uint8_t x = 0; x < VGA_WIDTH; x++)
		{
			terminal.buffer[get_screen_index(x, y)] = make_vga_entry(' ');
		}
	}

	update_cursor();

}

uint16_t make_colored_vga_entry(char c, uint8_t color)
{
	return ((uint16_t)c) | ((uint16_t) color) << 8;
}

uint16_t make_vga_entry(char c)
{
	return make_colored_vga_entry(c, terminal.color);
}

uint16_t get_screen_index(uint8_t column, uint8_t row)
{
	const uint16_t index = row * VGA_WIDTH + column;
	return index;
}

uint16_t get_current_screen_index()
{
	return get_screen_index(terminal.column, terminal.row);
}

void set_cursor(uint16_t location)
{
	write_byte(CRT_SIG, 14);
	write_byte(CRT_DATA, location >> 8); // High byte

	write_byte(CRT_SIG, 15);
	write_byte(CRT_DATA, location); // Low byte
}

void set_cursor_col(uint8_t column, uint8_t row)
{
	set_cursor(get_screen_index(column, row));
}

void update_cursor()
{
	set_cursor(get_current_screen_index());
}

uint8_t make_terminal_color(enum terminal_color fg, enum terminal_color bg)
{
	return fg | bg << 4;
}

void terminal_colored_putchar(char c, uint8_t color)
{

	switch (c)
	{
	/*	case '\b': // Backspace TODO: Implement better terminall class... apperentlly
			if (terminal.column == 0)
			{
				terminal.row--;
				terminal.column = VGA_WIDTH;
			} 
			else 
			{
				terminal.column -= 2;
			}
			terminal_colored_putchar(' ', color);
			break;*/
		case '\n': // 
			++terminal.row;
			terminal.column = 0;
			break;
		default:
			terminal.buffer[get_current_screen_index()] = make_colored_vga_entry(c, color);
			
			if (++terminal.column == VGA_WIDTH)
			{
				
				terminal.column = 0;
				
				if (++terminal.row == VGA_HEIGHT)
				{
					terminal.row = 0;
				}
				
			}
			break;
	}

	update_cursor();
}

void terminal_colored_putstring(const char* data, uint8_t color)
{
	for (int i = 0; i < strlen(data); i++)
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

