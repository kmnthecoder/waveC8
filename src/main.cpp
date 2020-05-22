#include <iostream>
#include <chrono>
#include <SDL.h>

#include "chip8.h"
#include "sdllayer.h"

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
        chip8.EmulateCycle();

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

    int scale = 10;
    int delay = 1;

    SdlLayer sdl("CHIP-8", SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale,
                 SCREEN_WIDTH, SCREEN_HEIGHT);

    myChip8.Initizalize();
    //myChip8.LoadFile("../roms/c8games/PONG");
    myChip8.LoadFile("../roms/tests/test2");

    int videoPitch = sizeof(myChip8.screen[0]) * SCREEN_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    bool quit = false;

    while (!quit)
    {
        quit = sdl.ProcessInput(myChip8.key);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > delay)
        {
            lastCycleTime = currentTime;

            myChip8.EmulateCycle();

            sdl.Update(myChip8.screen, videoPitch);
        }
    }

    /*
    for (int i = 0; i <= 4; i++)
    {
        myChip8.EmulateCycle();
    }
    */

    return 0;
}