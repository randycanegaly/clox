#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() { // static means only accessible from this file
  vm.stackTop = vm.stack; // set stackTop back to the first element in the stack
                          // - stack is empty
}

void initVM() { resetStack(); }

void freeVM() {}

void push(Value value) {
  *vm.stackTop =
      value; //. has higher precedence than *
             // get the stackTop pointer from vm first, then dereference it to
             // what stackTop points to assign value to that
  vm.stackTop++; // move the stack top pointer (indicator) to where the next
                 // push will occur
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

// called in interpret() below after parsing occured and we have a loaded chunk
static InterpretResult run() {
#define READ_BYTE()                                                            \
  (*vm.ip++) // get the value of the thing (byte) that ip points to and then
             // increment ip
#define READ_CONSTANT()                                                        \
  (vm.chunk->constants                                                         \
       .values[READ_BYTE()]) // Get the chunk in the VM structure
                             // The chunk's constants member is a ValueArray
                             // ValueArray is a struct wrapping the values
                             // dynamic array READ_BYTE() gets the byte value
                             // that ip points to, in this case it will be the
                             // byte for an index into the values dynamic array
                             // So READ_CONSTANT() returns the actual constant
                             // value at that index

#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = pop();                                                          \
    double a = pop();                                                          \
    push(a op b);                                                              \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");

    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(
        vm.chunk,
        (int)(vm.ip -
              vm.chunk->code)); // as instructions are executed in the chunk, ip
                                // moves along - increases this pointer math is
                                // the offset, the distance the ip is from the
                                // start of the chunk
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) { // get the byte that the instruction
                                         // pointer points to
      // switch on whatever that op code is, the case's will push values onto
      // the stack the last value pushed is the value of the expression entered
      // in stdin
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_NEGATE: {
      push(-pop());
      break;
    }
    case OP_RETURN: {
      printValue(
          pop()); // last one, prints the top value of the stack - the result
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

// from main.c #21
InterpretResult interpret(const char *source) {
  Chunk chunk;
  initChunk(&chunk);

  // we have a line of source and a chunk to load it into
  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }

  vm.chunk = &chunk;      // makes parsed loaded chunk available in the global
  vm.ip = vm.chunk->code; // sets instruction pointer in the global

  // at this point, compile() above succeeded so the local chunk variable has
  // been loaded with op codes and constant values. Now we need to take those op
  // codes and constants and calculate what their values are. That is done in
  // run()
  InterpretResult result = run();

  freeChunk(&chunk);
  return result;
}
