#include <stdio.h>

#include "debug.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ++\n", name);//print a header for the debug output
    for (int offset; offset < chunk->count;) {//don't increment in the loop condition, the function call below gives the new offset
        offset = disassembleInstruction(chunk, offset);
    }
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
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);//OP_RETURN is a simple instruction with no operands. 
                                                          //simpleInstruction will return the offset to the next instruction
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;  //we know a simple instruction is only one byte, so bump the offset by one byte and return it
                                //that's what increments the loop condition above
    }
}


