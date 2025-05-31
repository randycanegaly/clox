#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk *chunk;
  uint8_t *ip;            // a pointer to the next instruction to be be executed
  Value stack[STACK_MAX]; // stack is an array of Values of size STACK_MAX
  Value *stackTop;
  // a pointer to a Value, the element one past the element at
  // the top of the stack - the spot where the next push will go
  Obj *objects; // head of the linked list of objects
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

// extern says to the compiler - this is a declaration, the definition is
// elsewhere as required, then vm is defined only one place, in vm.c when
// object.c #includes vm.h, it gets access to vm to use
extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
