#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

/* set all chunk fields to zero/null*/
void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(
      &chunk->constants); // set the values member to be nulls/zeroes also
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code,
             chunk->capacity); // free the memory allocated for chunk
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk); // set all members to zero/null
}

/*put a byte in a Chunk*/
void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity <
      chunk->count + 1) { // don't have enough capacity to add the byte
    int oldCapacity = chunk->capacity; // remember current capacity
    chunk->capacity = GROW_CAPACITY(
        oldCapacity); // reset capacity to at least 8 or twice current capacity
    chunk->code = GROW_ARRAY(
        uint8_t, chunk->code, oldCapacity,
        chunk->capacity); // create a new coe array of the new capacity size
    chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] =
      byte; // the byte gets added at the count index, which is one past the
            // capacity of the old array before resizing
  chunk->lines[chunk->count] =
      line; // store the line number from the source file in the lines array
  chunk->count++; // increment count because we added another byte
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count -
         1; // return the index where the new constant was added
}
