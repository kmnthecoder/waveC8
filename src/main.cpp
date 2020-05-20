#include "chip8.h"

#include <iostream>

int main(int argc, char **argv)
{

    // Set up render and input system
    /*
    setupGraphics();
    setupInput();
    */

    // Init Chip8 system and load game into memory
    /*
    chip8.init();
    chip8.loadGame("pong");
    */

    // Emulation loop
    /*
    for (;;)
    {
        ** Emulate one cycle
        chip8.emulateCycle();

        ** if draw flag is set, update the screen
        if(chip8.drawFlag)
        {
            drawGraphics();
        }

        ** Store key press state (press and release)
        chip8.setKeys();
    }
    */
    Chip8 myChip8;

    myChip8.initizalize();
    myChip8.loadFile("../roms/c8games/PONG");

    for (int i = 0; i <= 4; i++) {
        myChip8.emulateCycle();
    }

    //myChip8.emulateCycle();

    return 0;
}