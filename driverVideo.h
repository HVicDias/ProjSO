#ifndef DRIVERVIDEO_H
#define DRIVERVIDEO_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64
 
/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */
 
#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */
 
#define bit(n) (1<<(n)) /* Set bit n to 1 */
 
/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

int strcmp(const char *a, const char *b);

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

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

vga_color bg = VGA_COLOR_BLACK;
vga_color fg = VGA_COLOR_LIGHT_GREY;



vga_color getColor(char* cor){
	if(strcmp(cor, "black") == 0){
		return VGA_COLOR_BLACK;
	}else if(strcmp(cor, "blue") == 0){
		return VGA_COLOR_BLUE;
	}else if(strcmp(cor, "green") == 0){ 
		return VGA_COLOR_GREEN;
	}else if(strcmp(cor, "cyan") == 0){
		return VGA_COLOR_CYAN;
	}else if(strcmp(cor, "red") == 0){
		return VGA_COLOR_RED;
	}else if(strcmp(cor, "magenta") == 0){
		return VGA_COLOR_MAGENTA;
	}else if(strcmp(cor, "brown") == 0){ 
		return VGA_COLOR_BROWN;
	}else if(strcmp(cor, "lgrey") == 0){
		return VGA_COLOR_LIGHT_GREY;
	}else if(strcmp(cor, "dgrey") == 0){
		return VGA_COLOR_DARK_GREY;
	}else if(strcmp(cor, "lblue") == 0){
		return VGA_COLOR_LIGHT_BLUE;
	}else if(strcmp(cor, "lgreen") == 0){ 
		return VGA_COLOR_LIGHT_GREEN;
	}else if(strcmp(cor, "lcyan") == 0){
		return VGA_COLOR_LIGHT_CYAN;
	}else if(strcmp(cor, "lred") == 0){
		return VGA_COLOR_LIGHT_RED;
	}else if(strcmp(cor, "lmagenta") == 0){
		return VGA_COLOR_LIGHT_MAGENTA;
	}else if(strcmp(cor, "lbrown") == 0){ 
		return VGA_COLOR_LIGHT_BROWN;
	}else if(strcmp(cor, "white") == 0){
		return VGA_COLOR_WHITE;
	}else{
		return VGA_COLOR_BLACK;
	}
}


uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

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

void terminal_alter_color(){
	terminal_color = vga_entry_color(fg, bg);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(terminal_buffer[index], terminal_color);
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

void info(){
	terminal_writestring("Desenvolvido por:");
	terminal_row++;
	terminal_column = (size_t) 0;
	terminal_writestring("Henrique Victorino Dias");
	terminal_row++;
	terminal_column = (size_t) 0;
	terminal_writestring("Gustavo Melo Cacau");
	terminal_row++;
	terminal_column = (size_t) 0;
	terminal_writestring("Lucas Rodrigues Sao Joao Miguel");
	terminal_row++;
	terminal_column = (size_t) 0;
	terminal_writestring("Version: 1.0.0.0");
	terminal_row++;
	terminal_column = (size_t) 0;
}

void reboot()
{
    uint8_t temp;
 
    asm volatile ("cli"); /* disable all interrupts */
 
    /* Clear all keyboard buffers (output and command buffers) */
    do
    {
        temp = inb(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
loop:
    asm volatile ("hlt"); /* if that didn't work, halt the CPU */
    goto loop; /* if a NMI is received, halt again */
}

void controle(const char* data, size_t size)
{
	char bufferAux[80] = {'\0'}, bufferAux2[80] = {'\0'};
	size_t i, j;
	
	for (i = 0; i < size; i++){
		if(data[i]!=' '){
			bufferAux[i] = data[i];
		}else{
			break;
		}
	}

	if(strcmp(bufferAux, "bgcolor") == 0){
		i++;
		for (j = i; j < size; j++){
			if(data[i]!=' '){
				bufferAux2[j-i] = data[j];
			}else{
				break;
			}
		}
		bufferAux2[++j] = '\0';

		bg = getColor(bufferAux2);
		terminal_alter_color();
	}else if(strcmp(bufferAux, "fgcolor") == 0){
		i++;
		for (j = i; j < size; j++){
			if(data[i]!=' '){
				bufferAux2[j-i] = data[j];
			}else{
				break;
			}
		}
		bufferAux2[++j] = '\0';

		fg = getColor(bufferAux2);
		terminal_alter_color();
	}else if(strcmp(bufferAux, "info") == 0){ 
		info();
	}else if(strcmp(bufferAux, "reboot") == 0){
		 reboot();
	}else if(strcmp(bufferAux, "clear") == 0){
		terminal_initialize();
	}
}


void terminal_control(int control, const char* data, size_t size,  size_t prevSize)
{
	if(control == 1){
		terminal_write(data, size);
		terminal_column = (size_t) 0;
	}else if(control == 2){
		controle(data, prevSize);
		terminal_row++;
		terminal_column = (size_t) 0;
	}
}

#endif
