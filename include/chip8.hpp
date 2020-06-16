#ifndef CHIP_H
#define CHIP_H

const int KEY_COUNT = 16;
const int MEMORY_SIZE = 4096;
const int REGISTER_COUNT = 16;
const int STACK_LEVELS = 16;
const int SCREEN_HEIGHT = 32;
const int SCREEN_WIDTH = 64;
const int FONTSET_SIZE = 80;
const int FONTSET_START_ADDRESS = 0x50;
const int START_ADDRESS = 0x200;

class Chip8
{
public:
    Chip8();
    ~Chip8();
    void LoadFile(const char *filename);
    void Initizalize();
    void EmulateCycle();

    unsigned int screen[SCREEN_HEIGHT * SCREEN_WIDTH]{};
    unsigned char key[KEY_COUNT]{};

private:
    unsigned short opcode{};
    unsigned char memory[MEMORY_SIZE]{};
    unsigned char V[REGISTER_COUNT]{}; // registers
    unsigned short I{};                // index register
    unsigned short pc{};               // program counter
    unsigned char delay_timer{};
    unsigned char sound_timer{};
    unsigned short stack[STACK_LEVELS]{};
    unsigned short sp{}; // stack pointer
    bool vwrap = true;   // can toggle vertical wrapping, on by default

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
    void FetchOpCode();
    void StepCpu();

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