#include "driverKeyboard.h"
#include "driverVideo.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

Keyboard keyboard;
int cod;

// Declarando a função do config.s
extern "C" void init_cpu();

// Seu tratador de interrupções
extern "C" void __interrupt_handler(uint32_t id)
{
    //cod = keyboard.attBuffer();
    if(id == 32){
        cod = keyboard.attBuffer();
    }else if(id == 33){
        terminal_control(cod,keyboard.buffer, keyboard.lenBuffer, keyboard.prevLenBuffer);
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