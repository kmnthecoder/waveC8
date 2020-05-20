#include "chip8.h"

#include <iostream>
#include <cstring>
#include <fstream>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int START_ADDRESS = 0x200;
const int FONTSET_SIZE = 80;
const int FONTSET_START_ADDRESS = 0x50;

unsigned char fontset[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, //1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
        0x90, 0x90, 0xF0, 0x10, 0x10, //4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
        0xF0, 0x10, 0x20, 0x40, 0x40, //7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
        0xF0, 0x90, 0xF0, 0x90, 0x90, //A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
        0xF0, 0x80, 0x80, 0x80, 0xF0, //C
        0xE0, 0x90, 0x90, 0x90, 0xE0, //D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
        0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

Chip8::Chip8()
{
}

Chip8::~Chip8()
{
}

//

void Chip8::initizalize()
{
    pc = START_ADDRESS; // program counter starts at this memory location
    opcode = 0;         // reset current opcode
    I = 0;              // reset index register
    sp = 0;             // reset stack pointer

    // clear display, stack, registers, memory
    memset(screen, 0, sizeof(screen));
    memset(stack, 0, sizeof(stack));
    memset(V, 0, sizeof(V));
    memset(memory, 0, sizeof(memory));

    // load fontset into memory
    for (int i = 0; i < FONTSET_SIZE; i++)
    {
        memory[i + FONTSET_START_ADDRESS] = fontset[i];
    }

    // reset timers
    delay_timer = 0;
    sound_timer = 0;

    // clear screen once
    drawFlag = true;
}

void Chip8::emulateCycle()
{
    // fetch opcode and increment pc
    opcode = memory[pc] << 8 | memory[pc + 1];
    pc += 2;

    std::cout << "Opcode: " << std::hex << std::uppercase << opcode << std::endl;

    // decode opcode
    // execute opcode

    // update timers
    if (delay_timer > 0)
    {
        delay_timer--;
    }

    if (sound_timer > 0)
    {
        if (sound_timer == 1)
        {
            std::cout << "BEEP" << std::endl;
        }
        sound_timer--;
    }
}

void Chip8::loadFile(const char *filename)
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