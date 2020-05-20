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
inline void Chip8::OP_8XY5() {}

// Store the value of register VY shifted right one bit in register VX
// Set register VF to the least significant bit prior to the shift
// VY is unchanged
inline void Chip8::OP_8XY6() {}

// Set register VX to the value of VY minus VX
// Set VF to 00 if a borrow occurs
// Set VF to 01 if a borrow does not occur
inline void Chip8::OP_8XY7() {}

// Store the value of register VY shifted left one bit in register VX¹
// Set register VF to the most significant bit prior to the shift
// VY is unchanged
inline void Chip8::OP_8XYE() {}

// Skip the following instruction if the value of register VX is not equal to the value of register VY
inline void Chip8::OP_9XY0() {}

// Store memory address NNN in register I
inline void Chip8::OP_ANNN() {}

// Jump to address NNN + V0
inline void Chip8::OP_BNNN() {}

// Set VX to a random number with a mask of NN
inline void Chip8::OP_CXNN()
{
    V[VX] = (rand() % 0xFF) & NN;
}

// Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
// Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
inline void Chip8::OP_DXYN() {}

// Skip the following instruction if the key corresponding to
// the hex value currently stored in register VX is pressed
inline void Chip8::OP_EX9E() {}

// Skip the following instruction if the key corresponding to
// the hex value currently stored in register VX is not pressed
inline void Chip8::OP_EXA1() {}

// Store the current value of the delay timer in register VX
inline void Chip8::OP_FX07() {}

// Wait for a keypress and store the result in register VX
inline void Chip8::OP_FX0A() {}

// Set the delay timer to the value of register VX
inline void Chip8::OP_FX15() {}

// Set the sound timer to the value of register VX
inline void Chip8::OP_FX18() {}

// Add the value stored in register VX to register I
inline void Chip8::OP_FX1E() {}

// Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
inline void Chip8::OP_FX29() {}

// Store the binary-coded decimal equivalent of the value stored in
// register VX at addresses I, I + 1, and I + 2
inline void Chip8::OP_FX33() {}

// Store the values of registers V0 to VX inclusive in memory starting at address I
// I is set to I + X + 1 after operation
inline void Chip8::OP_FX55() {}

// Fill registers V0 to VX inclusive with the values stored in memory starting at address I
// I is set to I + X + 1 after operation
inline void Chip8::OP_FX65() {}