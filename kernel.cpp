#include "driverKeyboard.h"
#include "driverVideo.h"
#include "registers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MY_REGISTER (*(volatile uint16_t *)0x2000u)

Keyboard keyboard;
int cod;

uint16_t mem[] = {0x0000, 0xb866, 0x0004, 0x0000, 0xbb66, 0x0001, 0x0000, 0xb966,
                  0x0028, 0x0010, 0x0000, 0xba66, 0x000d, 0x0000, 0x80cd, 0xb866,
                  0x0001, 0x0000, 0x0020, 0xbb66, 0x0000, 0x0000, 0x80cd, 0x6548,
                  0x6c6c, 0x206f, 0x6f77, 0x0030, 0x6c72, 0x2164, 0x000a, 0x0035};

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
    if (ssid == 128)
    {
        //eax == registers.r0
        //ebx == registers.r1
        //ecx == registers.r2
        //edx == registers.r3
        if (registers.r0 == 4)
        {
            terminal_control(1, (char *)registers.r2, (registers.r3 + 1), registers.r3);
        }
    }
}

extern "C" void kernel_main(void)
{
    terminal_initialize();
    init_cpu();
    uint16_t *ptr = (uint16_t *)0x2000;

    for (int i = 0; i < 32; i++)
    {
        ptr[i] = mem[i];
    }

    _run_app();
    ///Shift numbers 0x2A (42) and 0x36(54) caps number 0x3A(58)
    /* Initialize terminal interface */
    while (true)
    {
        /* code */
    }

    //func write
    //func read
}