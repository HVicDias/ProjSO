#ifndef DRIVERVIDEO_H
#define DRIVERVIDEO_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/reboot.h>

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

vga_color getColor(int num){
	switch (num)
	{
	case 0:
		return VGA_COLOR_BLACK;
		break;
	case 1:
		return VGA_COLOR_BLUE;
		break;
	case 2:
		return VGA_COLOR_GREEN;
		break;
	case 3:
		return VGA_COLOR_CYAN;
		break;
	case 4:
		return VGA_COLOR_RED;
		break;
	case 5:
		return VGA_COLOR_MAGENTA;
		break;
	case 6:
		return VGA_COLOR_BROWN;
		break;
	case 7:
		return VGA_COLOR_LIGHT_GREY;
		break;
	case 8:
		return VGA_COLOR_DARK_GREY;
		break;
	case 9:
		return VGA_COLOR_LIGHT_BLUE;
		break;
	case 10:
		return VGA_COLOR_LIGHT_GREEN;
		break;
	case 11:
		return VGA_COLOR_LIGHT_CYAN;
		break;
	case 12:
		return VGA_COLOR_LIGHT_RED;
		break;
	case 13:
		return VGA_COLOR_LIGHT_MAGENTA;
		break;
	case 14:
		return VGA_COLOR_LIGHT_BROWN;
		break;
	case 15:
		return VGA_COLOR_WHITE;
		break;
	default:
	return VGA_COLOR_BLACK;
		break;
	}
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
vga_color bg = VGA_COLOR_BLACK;
vga_color fg = VGA_COLOR_LIGHT_GREY;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(fg, bg);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { ++a; ++b; }
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}


void controle(const char* data, size_t size)
{
	char bufferAux[80];
	size_t i;
	for (i = 0; i < size; i++){
		if(data[i]!=' '){
			bufferAux[i] = data[i];
		}else{
			break;
		}
	}

	if(strcmp(bufferAux, "bgcolor") == 0){
		terminal_row++;
		terminal_putchar((int) data[i++]);
		terminal_column = (size_t) 0;
		terminal_row++;
		/*if((int) data[i++] == 5){
			terminal_row++;
		}else if((int) data[i++] == 35){
			terminal_row++;
			terminal_row++;
		}*/
		//bg = getColor((int) data[++i]);
		//terminal_initialize();
	}else if(strcmp(bufferAux, "fgcolor") == 0){
		terminal_color = vga_entry_color(getColor((int) data[i]), bg);
	}else if(strcmp(bufferAux, "info") == 0){ //devs e versao
		
	}else if(strcmp(bufferAux, "reboot") == 0){
		
	}else if(strcmp(bufferAux, "clear") == 0){
		bg = getColor(5);
		terminal_initialize();
	}
}


void terminal_control(int control, const char* data, size_t size,  size_t prevSize)
{
	if(control == 1){
		terminal_write(data, size);
		terminal_column = (size_t) 0;
	}else if(control == 2){
		terminal_row++;
		controle(data, prevSize);
	}
}

#endif
