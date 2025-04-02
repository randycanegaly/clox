#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity < 8 ? 8 : (capacity * 2)))

/*
 *A macro that takes the type of the array elements
 *A pointer to the array
 *The old number of elements in the array
 *The new number of elements allowed in the array
 *and converts number of elements to number of bytes for both the old and new counts
 *and casts the resulting reallocate() pointer to the correct type
*/
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
            sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate((pointer), sizeof(type) * (oldCount), 0)//pointer to the array to free, current size in bytes, newSize = 0


void* reallocate(void* pointer, size_t oldSize, size_t newSize);


#endif
