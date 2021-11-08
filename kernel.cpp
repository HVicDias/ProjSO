#include "driverKeyboard.h"
#include "driverVideo.h"
#include "register.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

Keyboard keyboard;
int cod;

int hexdump[] = {0000000, b866, 0004, 0000, bb66, 0001, 0000, b966, 0028,
                 0000010, 0000, ba66, 000d, 0000, 80cd, b866, 0001, 0000,
                 0000020, bb66, 0000, 0000, 80cd, 6548, 6c6c, 206f, 6f77,
                 0000030, 6c72, 2164, 000a,
                 0000035};

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