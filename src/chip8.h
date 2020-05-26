//#include <vector>

#ifndef CHIP_H
#define CHIP_H

/*
#include <random>

class Chip8
{
public:
    
private:

    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

    

    // opcodes defined in opcodes.cpp
    
};
*/

#include <cstdint>
#include <random>
#include <SDL.h>
//#include "opcodes.cpp"

const int KEY_COUNT = 16;
const int MEMORY_SIZE = 4096;
const int REGISTER_COUNT = 16;
const int STACK_LEVELS = 16;
const int SCREEN_HEIGHT = 32;
const int SCREEN_WIDTH = 64;
const int FONTSET_SIZE = 80;
const int FONTSET_START_ADDRESS = 0x50;


class Chip8
{
public:
    Chip8();
    ~Chip8();
    //void LoadROM(char const *filename);
    void LoadFile(const char *filename);

    void Initizalize();
    void EmulateCycle();

    void Cycle();

    //uint8_t keypad[KEY_COUNT]{};
    uint8_t key[KEY_COUNT]{};
    //uint32_t video[SCREEN_WIDTH * SCREEN_HEIGHT]{};

    //unsigned int video[SCREEN_HEIGHT * SCREEN_WIDTH]{};
    unsigned int screen[SCREEN_HEIGHT * SCREEN_WIDTH]{};
    //unsigned char keypad[16]{};

private:
    unsigned short opcode{};
    unsigned char memory[MEMORY_SIZE]{};

    //unsigned char registers[STACK_LEVELS]{}; // registers CHANGE
        unsigned char V[16u]{}; // registers CHANGE

    //unsigned short index{}; // index register CHANGE
    unsigned short I{};

    unsigned short pc{}; // program counter

    //unsigned char delay_timer{}; // CHANGE
    //unsigned char sound_timer{}; // CHANGE
    unsigned char delay_timer{}; // CHANGE
    unsigned char sound_timer{}; // CHANGE

    unsigned short stack[STACK_LEVELS]{};
    //std::vector<unsigned short> mStack;
    unsigned short sp{}; // stack pointer

    const unsigned char fontset[FONTSET_SIZE] =
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

    void UpdateTimers();
    void FetchOPCode();
    void StepCpu();


    /*
    void Table0();
    void Table8();
    void TableE();
    void TableF();

    // Do nothing
    void OP_NULL();

    // CLS
    void OP_00E0();

    // RET
    void OP_00EE();

    // JP address
    void OP_1nnn();

    // CALL address
    void OP_2nnn();

    // SE Vx, byte
    void OP_3xkk();

    // SNE Vx, byte
    void OP_4xkk();

    // SE Vx, Vy
    void OP_5xy0();

    // LD Vx, byte
    void OP_6xkk();

    // ADD Vx, byte
    void OP_7xkk();

    // LD Vx, Vy
    void OP_8xy0();

    // OR Vx, Vy
    void OP_8xy1();

    // AND Vx, Vy
    void OP_8xy2();

    // XOR Vx, Vy
    void OP_8xy3();

    // ADD Vx, Vy
    void OP_8xy4();

    // SUB Vx, Vy
    void OP_8xy5();

    // SHR Vx
    void OP_8xy6();

    // SUBN Vx, Vy
    void OP_8xy7();

    // SHL Vx
    void OP_8xyE();

    // SNE Vx, Vy
    void OP_9xy0();

    // LD I, address
    void OP_Annn();

    // JP V0, address
    void OP_Bnnn();

    // RND Vx, byte
    void OP_Cxkk();

    // DRW Vx, Vy, height
    void OP_Dxyn();

    // SKP Vx
    void OP_Ex9E();

    // SKNP Vx
    void OP_ExA1();

    // LD Vx, DT
    void OP_Fx07();

    // LD Vx, K
    void OP_Fx0A();

    // LD DT, Vx
    void OP_Fx15();

    // LD ST, Vx
    void OP_Fx18();

    // ADD I, Vx
    void OP_Fx1E();

    // LD F, Vx
    void OP_Fx29();

    // LD B, Vx
    void OP_Fx33();

    // LD [I], Vx
    void OP_Fx55();

    // LD Vx, [I]
    void OP_Fx65();

    

    typedef void (Chip8::*Chip8Func)();
    Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
    Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};
    */

   std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    inline void OP_0NNN();
    inline void OP_00E0();
    inline void OP_00EE();
    inline void OP_1NNN();
    inline void OP_2NNN();
    inline void OP_3XNN();
    inline void OP_4XNN();
    inline void OP_5XY0();
    inline void OP_6XNN();
    inline void OP_7XNN();
    inline void OP_8XY0();
    inline void OP_8XY1();
    inline void OP_8XY2();
    inline void OP_8XY3();
    inline void OP_8XY4();
    inline void OP_8XY5();
    inline void OP_8XY6();
    inline void OP_8XY7();
    inline void OP_8XYE();
    inline void OP_9XY0();
    inline void OP_ANNN();
    inline void OP_BNNN();
    inline void OP_CXNN();
    inline void OP_DXYN();
    inline void OP_EX9E();
    inline void OP_EXA1();
    inline void OP_FX07();
    inline void OP_FX0A();
    inline void OP_FX15();
    inline void OP_FX18();
    inline void OP_FX1E();
    inline void OP_FX29();
    inline void OP_FX33();
    inline void OP_FX55();
    inline void OP_FX65();
    //inline void OP_NULL();

    inline void Table0();
    inline void Table8();
    inline void TableE();
    inline void TableF();

    typedef void (Chip8::*OPCodeTable)();
    OPCodeTable table[0xF + 1]{};
    OPCodeTable table0[0xE + 1]{};
    OPCodeTable table8[0xE + 1]{};
    OPCodeTable tableE[0xE + 1]{};
    OPCodeTable tableF[0x65 + 1]{};
};

#endif // CHIP_H