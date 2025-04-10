#include <stdio.h>

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
    
    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);
    
    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant , 123);

    writeChunk(&chunk, OP_DIVIDE , 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 124);//pointer to chunk and the byte to be added
    printf("About to disassembleChunk()\n"); 
    disassembleChunk(&chunk, "test chunk");
    printf("\nAbout to interpret chunk\n");
    interpret(&chunk);
    freeVM(); 
    freeChunk(&chunk);

    return 0;
}
