#ifndef OPCODES_H
#define OPCODES_H

class OPCodes
{
public:
private:
    // Execute machine langeuage subroutine at address NNN
    void OP_0NNN();

    // Clear the screen
    void OP_00E0();

    // Return from a subroutine
    void OP_00EE();

    // Jump to address NNN
    void OP_1NNN();

    // Execute subroutine starting at address NNN
    void OP_2NNN();

    // Skip the following isntruction if the value of register VX equals NN
    void OP_3XNN();

    // Skip the following instruction if hte value of register VX is not equal to NN
    void OP_4XNN();

    // Skip the following instruction if the value of register VX is equal to
    // the value of register VY
    void OP_5XY0();

    // Store number NN in register VX
    void OP_6XNN();

    // Add the value NN to register VX
    void OP_7XNN();

    // Store the value of register VY in register VX
    void OP_8XY0();

    // Set VX to VX OR VY
    void OP_8XY1();

    // Set VX to VX AND VY
    void OP_8XY2();

    // Set VX to VX XOR VY
    void OP_8XY3();

    // Add the value of register VY to register VX
    // Set VF to 01 if a carry occurs
    // Set VF to 00 if a carry does not occur
    void OP_8XY4();

    // Subtract the value of register VY from register VX
    // Set VF to 00 if a borrow occurs
    // Set VF to 01 if a borrow does not occur
    void OP_8XY5();

    // Store the value of register VY shifted right one bit in register VX
    // Set register VF to the least significant bit prior to the shift
    // VY is unchanged
    void OP_8XY6();

    // Set register VX to the value of VY minus VX
    // Set VF to 00 if a borrow occurs
    // Set VF to 01 if a borrow does not occur
    void OP_8XY7();

    // Store the value of register VY shifted left one bit in register VX¹
    // Set register VF to the most significant bit prior to the shift
    // VY is unchanged
    void OP_8XYE();

    // Skip the following instruction if the value of register VX is not equal to the value of register VY
    void OP_9XY0();

    // Store memory addrtess NNN in register I
    void OP_ANNN();

    // Jump to address NNN + V0
    void OP_ANNN();

    // Jump to address NNN + V0
    void OP_BNNN();

    // Set VX to a random number with a mask of NN
    void OP_CXNN();

    // Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
    // Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
    void OP_DXYN();

    // Skip the following instruction if the key corresponding to
    // the hex value currently stored in register VX is pressed
    void OP_EX9E();

    // Skip the following instruction if the key corresponding to
    // the hex value currently stored in register VX is not pressed
    void OP_EXA1();

    // Store the current value of the delay timer in register VX
    void OP_FX07();

    // Wait for a keypress and store the result in register VX
    void OP_FX0A();

    // Set the delay timer to the value of register VX
    void OP_FX15();

    // Set the sound timer to the value of register VX
    void OP_FX18();

    // Add the value stored in register VX to register I
    void OP_FX1E();

    // Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
    void OP_FX29();

    // Store the binary-coded decimal equivalent of the value stored in
    // register VX at addresses I, I + 1, and I + 2
    void OP_FX33();

    // Store the values of registers V0 to VX inclusive in memory starting at address I
    // I is set to I + X + 1 after operation
    void OP_FX55();

    // Fill registers V0 to VX inclusive with the values stored in memory starting at address I
    // I is set to I + X + 1 after operation
    void OP_FX65();
};

#endif // OPCODES_H