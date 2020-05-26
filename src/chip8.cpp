#include <fstream> // reading files

#include "chip8.h"
#include "opcodes.cpp"

Chip8::Chip8()
{
    table[0x1] = &Chip8::OP_1NNN;
    table[0x2] = &Chip8::OP_2NNN;
    table[0x3] = &Chip8::OP_3XNN;
    table[0x4] = &Chip8::OP_4XNN;
    table[0x5] = &Chip8::OP_5XY0;
    table[0x6] = &Chip8::OP_6XNN;
    table[0x7] = &Chip8::OP_7XNN;
    table[0x9] = &Chip8::OP_9XY0;
    table[0xA] = &Chip8::OP_ANNN;
    table[0xB] = &Chip8::OP_BNNN;
    table[0xC] = &Chip8::OP_CXNN;
    table[0xD] = &Chip8::OP_DXYN;

    table[0x0] = &Chip8::Table0;
    table0[0x0] = &Chip8::OP_00E0;
    table0[0xE] = &Chip8::OP_00EE;

    table[0x8] = &Chip8::Table8;
    table8[0x0] = &Chip8::OP_8XY0;
    table8[0x1] = &Chip8::OP_8XY1;
    table8[0x2] = &Chip8::OP_8XY2;
    table8[0x3] = &Chip8::OP_8XY3;
    table8[0x4] = &Chip8::OP_8XY4;
    table8[0x5] = &Chip8::OP_8XY5;
    table8[0x6] = &Chip8::OP_8XY6;
    table8[0x7] = &Chip8::OP_8XY7;
    table8[0xE] = &Chip8::OP_8XYE;

    table[0xE] = &Chip8::TableE;
    tableE[0x1] = &Chip8::OP_EXA1;
    tableE[0xE] = &Chip8::OP_EX9E;

    table[0xF] = &Chip8::TableF;
    tableF[0x07] = &Chip8::OP_FX07;
    tableF[0x0A] = &Chip8::OP_FX0A;
    tableF[0x15] = &Chip8::OP_FX15;
    tableF[0x18] = &Chip8::OP_FX18;
    tableF[0x1E] = &Chip8::OP_FX1E;
    tableF[0x29] = &Chip8::OP_FX29;
    tableF[0x33] = &Chip8::OP_FX33;
    tableF[0x55] = &Chip8::OP_FX55;
    tableF[0x65] = &Chip8::OP_FX65;
}

Chip8::~Chip8()
{
}

void Chip8::Initizalize()
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
    for (unsigned int i = 0; i < FONTSET_SIZE; i++)
    {
        memory[i + FONTSET_START_ADDRESS] = fontset[i];
    }

    // reset timers
    delay_timer = 0;
    sound_timer = 0;
}

void Chip8::EmulateCycle()
{
    FetchOPCode();
    StepCpu();
    UpdateTimers();
}

void Chip8::StepCpu()
{
    ((*this).*(table[(opcode & 0xF000u) >> 12u]))();
}

void Chip8::FetchOPCode()
{
    opcode = (memory[pc] << 8u) | memory[pc + 1];
}

void Chip8::UpdateTimers()
{
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

void Chip8::LoadFile(const char *filename)
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
        for (long i = 0; i < bufferSize; i++)
        {
            memory[i + START_ADDRESS] = buffer[i];
        }

        delete[] buffer;
    }
}