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
    int cod;

    while(1){
        cod = keyboard.attBuffer();
        terminal_control(cod,keyboard.buffer, keyboard.lenBuffer, keyboard.prevLenBuffer);
    }

    //func write
    //func read
}