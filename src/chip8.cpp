#include "chip8.h"

#include <iostream>
#include <cstring>
#include <fstream>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int START_ADDRESS = 0x200;

chip8::chip8()
{
}

chip8::~chip8()
{
}

//

void chip8::initizalize()
{
    pc = START_ADDRESS; // program counter starts at this memory location
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

void chip8::loadFile(const char *filename)
{
    std::cout << "Attempting to load: " << filename << std::endl;

    // open file at path in binary mode and set pointer to the end
    std::ifstream myFile(filename, std::ios::binary | std::ios::ate);

    if (myFile.is_open())
    {
        std::cout << "Successfully loaded: " << filename << std::endl;

        // get file size and allocate to buffer to hold contents
        std::streampos bufferSize = myFile.tellg();
        char *buffer = new char[bufferSize];

        // fill buffer from start of file then close file stream
        myFile.seekg(0, std::ios::beg);
        myFile.read(buffer, bufferSize);
        myFile.close();

        // load file into memory, at starting address
        for (int i = 0; i < bufferSize; i++)
        {
            memory[i + START_ADDRESS] = buffer[i];
        }

        delete[] buffer;
    }
}