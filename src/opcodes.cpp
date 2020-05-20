#include "opcodes.h"
#include "chip8.h"

#define OP ((opcode & 0xF000) >> 12)
#define NNN (opcode & 0x0FFF)
#define NN (opcode & 0x00FF)
#define N (opcode & 0x000F)
#define VX ((opcode & 0x0F00) >> 8)
#define VY ((opcode & 0x00F0) >> 4)

void OPCodes::OP_0NNN()
{
}