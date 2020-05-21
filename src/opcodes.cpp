#include "chip8.h"

#include <stdlib.h> /* rand() */
#include <cstring>  /* memset */

#define OP ((opcode & 0xF000) >> 12)
#define NNN (opcode & 0x0FFF)
#define NN (opcode & 0x00FF)
#define N (opcode & 0x000F)
#define VX ((opcode & 0x0F00) >> 8)
#define VY ((opcode & 0x00F0) >> 4)

// Execute machine langeuage subroutine at address NNN
inline void Chip8::OP_0NNN() {}

// Clear the screen
inline void Chip8::OP_00E0()
{
    memset(screen, 0, sizeof(screen));
}

// Return from a subroutine
inline void Chip8::OP_00EE()
{
    sp--;
    pc = stack[sp];
}

// Jump to address NNN
inline void Chip8::OP_1NNN()
{
    pc = NNN;
}

// Execute subroutine starting at address NNN
inline void Chip8::OP_2NNN()
{
    stack[sp] = pc;
    sp++;
    pc = NNN;
}

// Skip the following instruction if the value of register VX equals NN
inline void Chip8::OP_3XNN()
{
    if (V[VX] == NN)
    {
        pc += 2;
    }
}

// Skip the following instruction if the value of register VX is not equal to NN
inline void Chip8::OP_4XNN()
{
    if (V[VX] != NN)
    {
        pc += 2;
    }
}

// Skip the following instruction if the value of register VX is equal to
// the value of register VY
inline void Chip8::OP_5XY0()
{
    if (V[VX] == V[VY])
    {
        pc += 2;
    }
}

// Store number NN in register VX
inline void Chip8::OP_6XNN()
{
    V[VX] = NN;
}

// Add the value NN to register VX
inline void Chip8::OP_7XNN()
{
    V[VX] += NN;
}

// Store the value of register VY in register VX
inline void Chip8::OP_8XY0()
{
    V[VX] = V[VY];
}

// Set VX to VX OR VY
inline void Chip8::OP_8XY1()
{
    V[VX] |= V[VY];
}

// Set VX to VX AND VY
inline void Chip8::OP_8XY2()
{
    V[VX] &= V[VY];
}

// Set VX to VX XOR VY
inline void Chip8::OP_8XY3()
{
    V[VX] ^= V[VY];
}

// Add the value of register VY to register VX
// Set VF to 01 if a carry occurs
// Set VF to 00 if a carry does not occur
inline void Chip8::OP_8XY4()
{
    ((V[VY] + V[VX]) > 0xFF) ? V[0xF] = 1 : V[0xF] = 0;
    V[VX] += V[VY];
}

// Subtract the value of register VY from register VX
// Set VF to 00 if a borrow occurs
// Set VF to 01 if a borrow does not occur
inline void Chip8::OP_8XY5()
{
    (V[VY] > V[VX]) ? V[0xF] = 0 : V[0xF] = 1;
    V[VX] -= V[VY];
}

// Store the value of register VY shifted right one bit in register VX
// Set register VF to the least significant bit prior to the shift
// VY is unchanged
inline void Chip8::OP_8XY6()
{
    V[0xF] = (V[VX] & 0x1);
    V[VX] >>= 1;
}

// Set register VX to the value of VY minus VX
// Set VF to 00 if a borrow occurs
// Set VF to 01 if a borrow does not occur
inline void Chip8::OP_8XY7()
{
    (V[VX] > V[VY]) ? V[0xF] = 0 : V[0xF] = 1;
    V[VX] = V[VY] - V[VX];
}

// Store the value of register VY shifted left one bit in register VX
// Set register VF to the most significant bit prior to the shift
// VY is unchanged
inline void Chip8::OP_8XYE()
{
    V[0xF] = (V[VX] & 0x80) >> 7;
    V[VX] <<= 1;
}

// Skip the following instruction if the value of register VX is not equal to the value of register VY
inline void Chip8::OP_9XY0()
{
    if (V[VX] != V[VY])
    {
        pc += 2;
    }
}

// Store memory address NNN in register I
inline void Chip8::OP_ANNN()
{
    I = NNN;
}

// Jump to address NNN + V0
inline void Chip8::OP_BNNN()
{
    pc = NNN + V[0];
}

// Set VX to a random number with a mask of NN
inline void Chip8::OP_CXNN()
{
    V[VX] = (rand() % 0xFF) & NN;
}

// Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
// Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
inline void Chip8::OP_DXYN()
{
    // X,Y coordinates of sprite
    unsigned short x = V[VX];
    unsigned short y = V[VY];

    unsigned short height = N;
    unsigned short pixel;

    // screen boundaries wrap
    unsigned short xPos = V[x] % SCREEN_WIDTH;
    unsigned short yPos = V[y] % SCREEN_HEIGHT;

    // reset register V[F]
    V[0xF] = 0;

    for (int yline = 0; yline < height; yline++) // loop over each row
    {
        pixel = memory[I + yline]; // fetch pixel from memory starting at location I

        for (int xline = 0; xline < 8; xline++) // loop over 8 bits of 1 row
        {
            unsigned short spritePixel = pixel & (0x80 >> xline);
            unsigned char *screenPixel = &screen[(yPos + yline) * SCREEN_WIDTH + (xPos) + xline];

            if (spritePixel) // if spritePixel is on
            {
                if (*screenPixel == 0xFFFFFFFF) // screenPixel on; collision detected
                {
                    V[0xF] = 1;
                }
                // XOR with spritePixel
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
    drawFlag = true; // update screen with drawFlag
}

// Skip the following instruction if the key corresponding to
// the hex value currently stored in register VX is pressed
inline void Chip8::OP_EX9E()
{
    if (key[V[VX]])
    {
        pc += 2;
    }
}

// Skip the following instruction if the key corresponding to
// the hex value currently stored in register VX is not pressed
inline void Chip8::OP_EXA1()
{
    if (!key[V[VX]])
    {
        pc += 2;
    }
}

// Store the current value of the delay timer in register VX
inline void Chip8::OP_FX07()
{
    V[VX] = delay_timer;
}

// Wait for a keypress and store the result in register VX
inline void Chip8::OP_FX0A()
{
    bool keyPress = false;

    for (int i = 0; i < 16; i++)
    {
        if (key[i] != 0)
        {
            V[VX] = i;
            keyPress = true;
        }
    }

    if (!keyPress)
    {
        pc -= 2;
    }
}

// Set the delay timer to the value of register VX
inline void Chip8::OP_FX15()
{
    delay_timer = V[VX];
}

// Set the sound timer to the value of register VX
inline void Chip8::OP_FX18()
{
    sound_timer = V[VX];
}

// Add the value stored in register VX to register I
inline void Chip8::OP_FX1E()
{
    if (I + V[VX] > 0xFFF)
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    I += V[VX];
}

// Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
inline void Chip8::OP_FX29()
{
    I = V[VX] * 0x05;
}

// Store the binary-coded decimal equivalent of the value stored in
// register VX at addresses I, I + 1, and I + 2
inline void Chip8::OP_FX33()
{
    memory[I] = V[VX] / 100;
    memory[I + 1] = (V[VX] / 10) % 10;
    memory[I + 2] = (V[VX] % 100) % 10;
}

// Store the values of registers V0 to VX inclusive in memory starting at address I
// I is set to I + X + 1 after operation
inline void Chip8::OP_FX55()
{
    for (int i = 0; i <= VX; i++)
    {
        memory[I + i] = V[i];
    }
}

// Fill registers V0 to VX inclusive with the values stored in memory starting at address I
// I is set to I + X + 1 after operation
inline void Chip8::OP_FX65()
{
    for (int i = 0; i <= VX; i++)
    {
        V[i] = memory[I + i];
    }
}