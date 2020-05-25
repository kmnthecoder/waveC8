#include "chip8.h"
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <random>
#include <iostream>
#include "opcodes.cpp"

//const unsigned int FONTSET_SIZE = 80;
const int START_ADDRESS = 0x200;

Chip8::Chip8()
    : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
    
    // Initialize PC
    pc = START_ADDRESS;

    // Load fonts into memory
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    // Initialize RNG
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

    table[0x0] = &Chip8::Table0;
    table[0x1] = &Chip8::OP_1NNN;
    table[0x2] = &Chip8::OP_2NNN;
    table[0x3] = &Chip8::OP_3XNN;
    table[0x4] = &Chip8::OP_4XNN;
    table[0x5] = &Chip8::OP_5XY0;
    table[0x6] = &Chip8::OP_6XNN;
    table[0x7] = &Chip8::OP_7XNN;
    table[0x8] = &Chip8::Table8;
    table[0x9] = &Chip8::OP_9XY0;
    table[0xA] = &Chip8::OP_ANNN;
    table[0xB] = &Chip8::OP_BNNN;
    table[0xC] = &Chip8::OP_CXNN;
    table[0xD] = &Chip8::OP_DXYN;
    table[0xE] = &Chip8::TableE;
    table[0xF] = &Chip8::TableF;

    table0[0x0] = &Chip8::OP_00E0;
    table0[0xE] = &Chip8::OP_00EE;

    table8[0x0] = &Chip8::OP_8XY0;
    table8[0x1] = &Chip8::OP_8XY1;
    table8[0x2] = &Chip8::OP_8XY2;
    table8[0x3] = &Chip8::OP_8XY3;
    table8[0x4] = &Chip8::OP_8XY4;
    table8[0x5] = &Chip8::OP_8XY5;
    table8[0x6] = &Chip8::OP_8XY6;
    table8[0x7] = &Chip8::OP_8XY7;
    table8[0xE] = &Chip8::OP_8XYE;

    tableE[0x1] = &Chip8::OP_EXA1;
    tableE[0xE] = &Chip8::OP_EX9E;

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
    //opcode = 0;         // reset current opcode
    //I = 0;              // reset index register
    //sp = 0;             // reset stack pointer

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
    //delayTimer = 0;
    //soundTimer = 0;

    // clear screen once
    //drawFlag = true;
}

void Chip8::EmulateCycle()
{
    FetchOPCode();
    // debug
    //std::cout << "Opcode: " << std::hex << std::uppercase << opcode << std::endl;
    //pc += 2;

    StepCpu();
    UpdateTimers();
}

void Chip8::StepCpu()
{
    // decode/execute opcode
    //std::cout << "Opcode: " << ((*this).*(table[(opcode & 0xF000) >> 12]))() << std::endl;
    ((*this).*(table[(opcode & 0xF000u) >> 12u]))();
}

void Chip8::FetchOPCode()
{
    opcode = (memory[pc] << 8u) | memory[pc + 1];
    //pc += 2;
}

void Chip8::UpdateTimers()
{
    // update timers
    if (delayTimer > 0)
    {
        delayTimer--;
    }

    if (soundTimer > 0)
    {
        if (soundTimer == 1)
        {
            std::cout << "BEEP" << std::endl;
        }
        soundTimer--;
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

/*
void Chip8::Table0()
{
    ((*this).*(table0[opcode & 0x000Fu]))();
}

void Chip8::Table8()
{
    ((*this).*(table8[opcode & 0x000Fu]))();
}

void Chip8::TableE()
{
    ((*this).*(tableE[opcode & 0x000Fu]))();
}

void Chip8::TableF()
{
    ((*this).*(tableF[opcode & 0x00FFu]))();
}

void Chip8::OP_NULL()
{
}

void Chip8::OP_00E0()
{
    memset(video, 0, sizeof(video));
}

void Chip8::OP_00EE()
{
    --sp;
    pc = stack[sp];
}

void Chip8::OP_1nnn()
{
    uint16_t address = opcode & 0x0FFFu;

    pc = address;
}

void Chip8::OP_2nnn()
{
    uint16_t address = opcode & 0x0FFFu;

    stack[sp] = pc;
    ++sp;
    pc = address;
}

void Chip8::OP_3xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if (registers[Vx] == byte)
    {
        pc += 2;
    }
}

void Chip8::OP_4xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if (registers[Vx] != byte)
    {
        pc += 2;
    }
}

void Chip8::OP_5xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vx] == registers[Vy])
    {
        pc += 2;
    }
}

void Chip8::OP_6xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    registers[Vx] = byte;
}

void Chip8::OP_7xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    registers[Vx] += byte;
}

void Chip8::OP_8xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] = registers[Vy];
}

void Chip8::OP_8xy1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] |= registers[Vy];
}

void Chip8::OP_8xy2()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] &= registers[Vy];
}

void Chip8::OP_8xy3()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8xy4()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    uint16_t sum = registers[Vx] + registers[Vy];

    if (sum > 255U)
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] = sum & 0xFFu;
}

void Chip8::OP_8xy5()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vx] > registers[Vy])
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] -= registers[Vy];
}

void Chip8::OP_8xy6()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    // Save LSB in VF
    registers[0xF] = (registers[Vx] & 0x1u);

    registers[Vx] >>= 1;
}

void Chip8::OP_8xy7()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vy] > registers[Vx])
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OP_8xyE()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    // Save MSB in VF
    registers[0xF] = (registers[Vx] & 0x80u) >> 7u;

    registers[Vx] <<= 1;
}

void Chip8::OP_9xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vx] != registers[Vy])
    {
        pc += 2;
    }
}

void Chip8::OP_Annn()
{
    uint16_t address = opcode & 0x0FFFu;

    index = address;
}

void Chip8::OP_Bnnn()
{
    uint16_t address = opcode & 0x0FFFu;

    pc = registers[0] + address;
}

void Chip8::OP_Cxkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    registers[Vx] = randByte(randGen) & byte;
}

void Chip8::OP_Dxyn()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint8_t height = opcode & 0x000Fu;

    // Wrap if going beyond screen boundaries
    uint8_t xPos = registers[Vx] % SCREEN_WIDTH;
    uint8_t yPos = registers[Vy] % SCREEN_HEIGHT;

    registers[0xF] = 0;

    for (unsigned int row = 0; row < height; ++row)
    {
        uint8_t spriteByte = memory[index + row];

        for (unsigned int col = 0; col < 8; ++col)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t *screenPixel = &video[(yPos + row) * SCREEN_WIDTH + (xPos + col)];

            // Sprite pixel is on
            if (spritePixel)
            {
                // Screen pixel also on - collision
                if (*screenPixel == 0xFFFFFFFF)
                {
                    registers[0xF] = 1;
                }

                // Effectively XOR with the sprite pixel
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void Chip8::OP_Ex9E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    uint8_t key = registers[Vx];

    if (keypad[key])
    {
        pc += 2;
    }
}

void Chip8::OP_ExA1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    uint8_t key = registers[Vx];

    if (!keypad[key])
    {
        pc += 2;
    }
}

void Chip8::OP_Fx07()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    registers[Vx] = delayTimer;
}

void Chip8::OP_Fx0A()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (keypad[0])
    {
        registers[Vx] = 0;
    }
    else if (keypad[1])
    {
        registers[Vx] = 1;
    }
    else if (keypad[2])
    {
        registers[Vx] = 2;
    }
    else if (keypad[3])
    {
        registers[Vx] = 3;
    }
    else if (keypad[4])
    {
        registers[Vx] = 4;
    }
    else if (keypad[5])
    {
        registers[Vx] = 5;
    }
    else if (keypad[6])
    {
        registers[Vx] = 6;
    }
    else if (keypad[7])
    {
        registers[Vx] = 7;
    }
    else if (keypad[8])
    {
        registers[Vx] = 8;
    }
    else if (keypad[9])
    {
        registers[Vx] = 9;
    }
    else if (keypad[10])
    {
        registers[Vx] = 10;
    }
    else if (keypad[11])
    {
        registers[Vx] = 11;
    }
    else if (keypad[12])
    {
        registers[Vx] = 12;
    }
    else if (keypad[13])
    {
        registers[Vx] = 13;
    }
    else if (keypad[14])
    {
        registers[Vx] = 14;
    }
    else if (keypad[15])
    {
        registers[Vx] = 15;
    }
    else
    {
        pc -= 2;
    }
}

void Chip8::OP_Fx15()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    delayTimer = registers[Vx];
}

void Chip8::OP_Fx18()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    soundTimer = registers[Vx];
}

void Chip8::OP_Fx1E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    index += registers[Vx];
}

void Chip8::OP_Fx29()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t digit = registers[Vx];

    index = FONTSET_START_ADDRESS + (5 * digit);
}

void Chip8::OP_Fx33()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t value = registers[Vx];

    // Ones-place
    memory[index + 2] = value % 10;
    value /= 10;

    // Tens-place
    memory[index + 1] = value % 10;
    value /= 10;

    // Hundreds-place
    memory[index] = value % 10;
}

void Chip8::OP_Fx55()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i)
    {
        memory[index + i] = registers[i];
    }
}

void Chip8::OP_Fx65()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i)
    {
        registers[i] = memory[index + i];
    }
}
*/