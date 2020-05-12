//#include <vector>
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class chip8
{
public:
    chip8();
    ~chip8();
    void helloWorld();
    //
    void initizalize();
    void emulateCycle();

private:
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16]; // registers
    unsigned short I;    // index register
    unsigned short pc;   // program counter
    unsigned char gfx[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[16];
    //std::vector<unsigned short> mStack;
    unsigned short sp; // stack pointer
    unsigned char key[16];
};