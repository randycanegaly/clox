#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    initVM(); 

    Chunk chunk;
    initChunk(&chunk);
    
    int constant = addConstant(&chunk, 1.2);//add 1.2 to the ValueArray of constants in chunk, returned is the index of 1.2 in that array
    writeChunk(&chunk, OP_CONSTANT, 123);//opcode into chunk with line number from the source file
    writeChunk(&chunk, constant, 123);//index to constant in the constants array gets written into chunk

    writeChunk(&chunk, OP_RETURN, 123);//pointer to chunk and the byte to be added
    
    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM(); 
    freeChunk(&chunk);

    return 0;
}
