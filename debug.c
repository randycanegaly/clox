#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);//print a header for the debug output
    for (int offset; offset < chunk->count;) {//don't increment in the loop condition, the function call below gives the new offset
        offset = disassembleInstruction(chunk, offset);
    }
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];//+1 means get the byte after the opcode
    printf("%-16s %4d '", name, constant);//prints opcode name and the byte representing the index into the constants array
    printValue(chunk->constants.values[constant]);//prints actual double value of the constant
    printf("'\n");
    return offset + 2;//return the offset to the next instruction, 1 after the constant index 
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);//print a header for the debug output
    return offset + 1;//we know a simple instruction is only one byte, so bump the offset by one byte and return it
                      //that's what increments the loop condition above
}

int disassembleInstruction(Chunk* chunk, int offset) {//will initially be offset = 0
    printf("%04d ", offset);//print a header for debug output
    uint8_t instruction = chunk->code[offset];//the fixed-size 8-bit integer of the instruction at the offset position in the array that code points to
    switch (instruction) {//switch on the integer value
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);//OP_RETURN is a simple instruction with no operands. 
                                                          //simpleInstruction will return the offset to the next instruction
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;  //we assume that this error/unknown instruction is only one byte, so bump the offset by one byte and return it
                                //that's what increments the loop condition above
    }
}


