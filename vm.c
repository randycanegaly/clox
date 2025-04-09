#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {//static means only accessible from this file
    vm.stackTop = vm.stack;//set stackTop back to the first element in the stack - stack is empty
}

void initVM() {
    resetStack();
}

void freeVM() {
}

void push(Value value) {
    *vm.stackTop = value;//. has higher precedence than *
                         //get the stackTop pointer from vm first, then dereference it to what 
                         //stackTop points to
                         //assign value to that
    vm.stackTop++;//move the stack top pointer (indicator) to where the next push will occur
}

int pop() {
    vm.stackTop--;
    return *vm.stackTop;
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
#ifdef DEBUG_TRACE_EXECUTION
        if (vm.stack == vm.stackTop)
            printf("        [ Stack is Empty ]");
        else
            printf("        ");

        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));//as instructions are executed in the chunk, ip moves along - increases
                                                                         //this pointer math is the offset, the distance the ip is from the start of the chunk
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            } 
            case OP_NEGATE: push(-pop()); break; 
            case OP_RETURN:  {
                printValue(pop());
                printf("\n");
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


