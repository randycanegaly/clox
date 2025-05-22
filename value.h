#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

// ch19 added for object value
typedef enum { VAL_BOOL, VAL_NIL, VAL_NUMBER, VAL_OBJ } ValueType;

typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
    Obj *obj; // ch19 added pointer to obj in heap
  } as;
} Value;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
// ch19 add to test for object type
// 'value' is of type Value. .type returns the ValueType
// test if equals VAL_OBJ ValueType
#define IS_OBJ(value) ((value).type == VAL_OBJ)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)
// ch19 get Obj* pointer out of the Value's union
#define AS_OBJ(value) ((value).as.obj)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
// ch19 takes a pointer
// uses compound literal and designated initiliazer
// to create a Value with type set to VAL_OBJ
// and obj in the union set to a pointer to an Obj
#define OBJ_VAL(object) ((Value){VAL_OBJ, {.obj = (Obj *)object}})

typedef struct { // a dynamic array holding values
  int capacity;
  int count;
  Value *values;
} ValueArray;

bool valuesEqual(Value a, Value b);

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void printValue(Value value);

#endif
