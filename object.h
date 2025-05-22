#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

// ch19 take a Value
// get the Obj* pointer out of Value's union
// get ObjType of the Obj
#define OBJ_TYPE(value) (AS_OBJ(value)->type)
// ch19 takes a Value
// returns true if object is an OBJ_STRING
#define IS_STRING(value) isObjType(value, OBJ_STRING)

// ch19 get the ObjString* out of the Value
// because of the memory structure of nested structs
// you can grab the Obj* out of the Value
// and cast it to an ObjString*
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))

// ch19 get the char* out of the Value
// do the above but grab the pointer to
// the start of the chars array in the ObjString
#define AS_CSTRING(value) ((ObjString *)AS_OBJ(value))->chars

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
};

struct ObjString {
  Obj obj; // inherits from Obj
  int length;
  char *chars;
};

// ch19 it's a Value with type VAL_OBJ
// && get the type of its Obj
// compare it to the type passed in
static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
