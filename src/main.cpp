#include <iostream>
#include <chrono>

#include "chip8.hpp"
#include "sdllayer.hpp"

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        std::cerr << "Format: <SCALE> <DELAY> <FILEPATH>" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int scale = std::stoi(argv[1]);
    int delay = std::stoi(argv[2]);
    const char *file = argv[3];

    SdlLayer sdl("CHIP-8 Emulator by kmnthecoder", SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale,
                 SCREEN_WIDTH, SCREEN_HEIGHT);
    Chip8 myChip8;

    myChip8.Initizalize();
    myChip8.LoadFile(file);

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

    return 0;
}