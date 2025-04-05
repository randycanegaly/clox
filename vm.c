#include <stdio.h>

#include "common.h"
#include "vm.h"

VM vm;

void initVM() {
}

void freeVM() {
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)//get the value of the thing (byte) that ip points to and then increment ip
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])//Get the chunk in the VM structure
                                                                 //The chunk's constants member is a ValueArray
                                                                 //ValueArray is a struct wrapping the values dynamic array
                                                                 //READ_BYTE() gets the byte value that ip points to,
                                                                 //in this case it will be the byte for an index into the values dynamic array
                                                                 //So READ_CONSTANT() returns the actual constant value at that index
    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            } 
            case OP_RETURN:  {
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;//the pointer to the next 8 bit instruction to execute gets assigned
                           //the address of the start of the chunk's code array (of instructions)
    return run();
}


