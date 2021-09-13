#include "driverKeyboard.h"
#include "driverVideo.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


extern "C" void kernel_main(void)
{
    ///Shift numbers 0x2A (42) and 0x36(54) caps number 0x3A(58)
    /* Initialize terminal interface */
    Keyboard keyboard;
    terminal_initialize();
    int value, cod;

    while(1){
        if (inb(0x64)&1)
        {
            value = inb(0x60); //le o codigo do buffer
            int cod = keyboard.attBuffer(value);
            terminal_control(cod,keyboard.buffer, keyboard.lenBuffer);
            if(cod == 2){
                keyboard.lenBuffer = 0;
                keyboard.posBuffer = 0;
            }
        }
    }
}