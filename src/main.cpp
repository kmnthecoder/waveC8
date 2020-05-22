#include <iostream>
#include <chrono>
#include <SDL.h>

#include "chip8.h"
#include "sdllayer.h"

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        std::cerr << "Format: <SCALE> <DELAY> <FILENAME>" << std::endl;
        std::exit(EXIT_FAILURE);
        //return 0;
    }

    int scale = std::stoi(argv[1]);
    int delay = std::stoi(argv[2]);
    const char *file = argv[3];

    SdlLayer sdl("CHIP-8", SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale,
                 SCREEN_WIDTH, SCREEN_HEIGHT);

    Chip8 myChip8;
    myChip8.Initizalize();
    myChip8.LoadFile(file);

    int videoPitch = sizeof(myChip8.screen[0]) * SCREEN_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    bool quit = false;

    /*
    unsigned int t1;
    unsigned int t2;
    unsigned int elapsed;
    unsigned int remaining;
    unsigned int TICKS = 500;
    unsigned int interval = 1000 / TICKS;
    */

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

        /*
        t1 = SDL_GetTicks();
        quit = sdl.ProcessInput(myChip8.key);
        myChip8.EmulateCycle();
        sdl.Update(myChip8.screen, videoPitch);
        t2 = SDL_GetTicks();
        elapsed = t2 - t1;
        remaining = interval - elapsed;
        if (elapsed < interval)
        {
            SDL_Delay(remaining);
            elapsed = interval;
        }
    */
    }

    return 0;
}