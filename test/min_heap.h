//*****************************************************************************************

//  min_heap.h  -   Min heap header file

//*****************************************************************************************

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD    256 

//*****************************************************************************************

typedef struct {        // Heap node structure
    char data[256];         // pointer to the word
    size_t freq;        // freq of word
} heap_node;

typedef struct {            // Min heap structure
    heap_node* nodes;       // Array of heap nodes
    size_t size;            // size of the heap
    size_t capacity;        // Max capacity of the heap
} min_heap;

//*****************************************************************************************

// Function declaration for min heap 
int heap_node_compare(const void* a, const void* b);
min_heap* init_min_heap(size_t capacity);
void min_heap_insert(min_heap* heap, char* data, size_t freq);
void free_min_heap(min_heap* heap);

#endif
//*****************************************************************************************