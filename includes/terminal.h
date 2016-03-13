#ifndef __TERMINAL_H
#define __TERMINAL_H 1

#include "system.h"

#define VIDEO_MEMORY_LOCATION 0xB8000
#define VGA_WIDTH 80 // Terminal can have 80 chars
#define VGA_HEIGHT 25 // by 25... I assume
#define CRT_SIG 0x3D4
#define CRT_DATA 0x3D5


/**
 * Colors of the terminal
 */
enum terminal_color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

/**
 * Terminal struct that holds all of the info about the terminal's state
 */
struct vga_terminal {
	uint8_t row, column;
	uint8_t color;
	uint16_t* buffer;
} terminal;

/**
 * Init the terminal with needed info
 */
void init_terminal();
/**
 *Make a colored VGA entry that will be sent to the display
 * c - character used
 * color - Color of the VGA entry
 */
uint16_t make_colored_vga_entry(char c, uint8_t color);
/**
 * Make a VGA entry
 * 2 bytes of data that contains the string & color of text
 * c - char used
 */
uint16_t make_vga_entry(char c);
/** TODO: Method header and docs are wrong
 * Find the index of a place in the screen buffer
 * row - x pos on screen
 * column - y pos on screen
 */
uint16_t get_screen_index(uint8_t row, uint8_t column);
/**
 * The current index of the screen buffer
 */
uint16_t get_current_screen_index();
/**
 * Set the cursor to a screen index
 * location - Location in video memory for the cursor.
 *            Use get_screen_index to make this value
 */
void set_cursor(uint16_t location);
/**
 * Set the cursor's location to a column and row.
 * column - The column in the VGA table
 * row    - The row in the VGA table
 */
void set_cursor_col(uint8_t column, uint8_t row);
/**
 * Update the cursor's location to where it should be on the screen.
 */
void update_cursor();
/**
 * Make a color that can be sent to the VGA adapter
 */
uint8_t make_terminal_color(enum terminal_color fg, enum terminal_color bg);
/**
 * Write a character to the VGA adapter
 */
void terminal_putchar(char c);
/**
 * Write a string to the display using the default
 * terminal color
 * data - String to write to the VGA adapter
 */
void terminal_putstring(const char* data);
/**
 * Write a character to the VGA adapter
 * c - character to write
 * color - color of the text, see make_terminal_color
 */
void terminal_colored_putchar(char c, uint8_t color);
/**
 * Write a string to the VGA adapter
 * data - string
 * color - color of the text, see make_terminal_color
 */
void terminal_colored_putstring(const char* data, uint8_t color);

void terminal_putdec(const unsigned number);

#endif
