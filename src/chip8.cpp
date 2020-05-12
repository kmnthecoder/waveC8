#include "chip8.h"

#include <iostream>
#include <string.h>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;

chip8::chip8()
{
}

chip8::~chip8()
{
}

void chip8::helloWorld()
{
    std::cout << "Hello world from chip8!" << std::endl;
}

//

void chip8::initizalize()
{
    pc = 0x200; // program counter starts at this memory location
    opcode = 0; // reset current opcode
    I = 0;      // reset index register
    sp = 0;     // reset stack pointer

    // clear display, stack, registers, memory
    memset(gfx, 0, SCREEN_HEIGHT * SCREEN_WIDTH);
    memset(stack, 0, 16);
    memset(V, 0, 16);
    memset(memory, 0, 4096);
}

void chip8::emulateCycle()
{
}