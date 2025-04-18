#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;//renames an existing type to 'Value'

typedef struct {//a dynamic array holding values
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value); 
void freeValueArray(ValueArray* array); 
void printValue(Value value);

#endif
