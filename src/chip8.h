//#include <vector>

#ifndef CHIP_H
#define CHIP_H

/*
#include <random>


extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;
extern const unsigned int START_ADDRESS;
extern const unsigned int FONTSET_SIZE;
extern const unsigned int FONTSET_START_ADDRESS;

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
    //uint32_t screen[64*32];

private:
    unsigned short opcode{};
    unsigned char memory[4096u]{};
    unsigned char V[16u]{}; // registers
    unsigned short I{};    // index register
    unsigned short pc{};   // program counter

    unsigned char delay_timer{};
    unsigned char sound_timer{};
    unsigned short stack[16u]{};
    //std::vector<unsigned short> mStack;
    unsigned short sp{}; // stack pointer

    const unsigned char fontset[80u] =
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

    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

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
*/




#include <cstdint>
#include <random>
#include <SDL.h>


const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;


class Chip8
{
public:
	Chip8();
	void LoadROM(char const* filename);
	void Cycle();

	uint8_t keypad[16u]{};
	//uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{};

    unsigned int video[64 * 32]{};
    //unsigned char keypad[16]{};


private:
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

	uint8_t memory[MEMORY_SIZE]{};
	uint8_t registers[REGISTER_COUNT]{};
	uint16_t index{};
	uint16_t pc{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint16_t stack[STACK_LEVELS]{};
	uint8_t sp{};
	uint16_t opcode{};

	std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
	Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};
};



#endif // CHIP_H