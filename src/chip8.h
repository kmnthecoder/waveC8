//#include <vector>

#ifndef CHIP_H
#define CHIP_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int START_ADDRESS;
extern const int FONTSET_SIZE;
extern const int FONTSET_START_ADDRESS;

class chip8
{
public:
    bool drawFlag;

    chip8();
    ~chip8();

    void initizalize();
    void emulateCycle();
    void loadFile(const char *filename);

private:
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16]; // registers
    unsigned short I;    // index register
    unsigned short pc;   // program counter
    unsigned char screen[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[16];
    //std::vector<unsigned short> mStack;
    unsigned short sp; // stack pointer
    unsigned char key[16];
};

#endif // CHIP_H