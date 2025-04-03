#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    
    int constant = addConstant(&chunk, 1.2);//add 1.2 to the ValueArray of constants in chunk, returned is the index of 1.2 in that array
    writeChunk(&chunk, OP_CONSTANT);//opcode into chunk
    writeChunk(&chunk, constant);//index to constant in the constants array gets written into chunk

    writeChunk(&chunk, OP_RETURN);//pointer to chunk and the byte to be added
    
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
