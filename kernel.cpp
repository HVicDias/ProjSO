#include "driverKeyboard.h"
#include "driverVideo.h"
#include "registers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

Keyboard keyboard;
int cod;

uint16_t mem[] = {0x0000, 0xb866, 0x0004, 0x0000, 0xbb66, 0x0001, 0x0000, 0xb966, 0x0028,
                  0x0010, 0x0000, 0xba66, 0x000d, 0x0000, 0x80cd, 0xb866, 0x0001, 0x0000,
                  0x0020, 0xbb66, 0x0000, 0x0000, 0x80cd, 0x6548, 0x6c6c, 0x206f, 0x6f77,
                  0x0030, 0x6c72, 0x2164, 0x000a,
                  0x0035};

//Declarando a função do config.s
extern "C" void init_cpu();

extern "C" void _run_app();

//Tratador de interrupções
extern "C" void __interrupt_handler(uint32_t ssid, Registers &registers)
{
    //cod = keyboard.attBuffer();
    if (ssid == 33)
    {
        cod = keyboard.attBuffer();
        terminal_control(cod, keyboard.buffer, keyboard.lenBuffer, keyboard.prevLenBuffer);
    }
}

extern "C" void kernel_main(void)
{
    terminal_initialize();
    init_cpu();
    ///Shift numbers 0x2A (42) and 0x36(54) caps number 0x3A(58)
    /* Initialize terminal interface */
    while (true)
    {
        /* code */
    }

    //func write
    //func read
}