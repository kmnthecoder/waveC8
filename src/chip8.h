//#include <vector>

#ifndef CHIP_H
#define CHIP_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int START_ADDRESS;
extern const int FONTSET_SIZE;
extern const int FONTSET_START_ADDRESS;

class Chip8
{
public:
    bool drawFlag;

    Chip8();
    ~Chip8();

    void Initizalize();
    void EmulateCycle();
    void LoadFile(const char *filename);

    //unsigned char GetScreen(int index);
    //unsigned char screen[64 * 32];
    unsigned int screen[64 * 32]{};
    //uint32_t screen[64*32];
    //unsigned char key[16]{};
    uint8_t key[16]{};

private:
    unsigned short opcode{};
    unsigned char memory[4096]{};
    unsigned char V[16]{}; // registers
    unsigned short I{};    // index register
    unsigned short pc{};   // program counter

    unsigned char delay_timer{};
    unsigned char sound_timer{};
    unsigned short stack[16]{};
    //std::vector<unsigned short> mStack;
    unsigned short sp{}; // stack pointer

    const unsigned char fontset[80] =
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

    // opcodes defined in opcodes.cpp
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