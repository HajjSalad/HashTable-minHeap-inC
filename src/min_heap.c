//******************************************************************************************************

//  min_heap.c  -   Min Heap implementation

//******************************************************************************************************

#include "min_heap.h"
#include <stdio.h>

//******************************************************************************************************

// Compare head nodes by frequency
int heap_node_compare(const void* a, const void* b) {
    return ((heap_node*)a)->freq - ((heap_node*)b)->freq;
} 

// Initialize a new min heap and return a pointer to it
min_heap* init_min_heap(size_t capacity) {
    if (capacity <= 0) return NULL;

    // Allocate memory for the heap
    min_heap* heap = malloc(sizeof(min_heap));
    if (heap == NULL) {
        fprintf(stderr, "Memory alloc failed for min heap");
        return NULL;
    }

    // Allocate memory for the heap nodes
    heap->nodes = malloc(capacity*(sizeof(heap_node)));
    if (heap->nodes == NULL) {
        free(heap);             // Free the allocated heap
        fprintf(stderr, "Memory alloc failed for heap nodes");
        return NULL;
    }

    for (size_t i=0; i<capacity; i++) {
        heap->nodes[i].data[0] = '\0';
        heap->nodes[i].freq = 0;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Insert into min-heap
void min_heap_insert(min_heap* heap, char* data, size_t freq) {

    // If heap size less than capacity
    if (heap->size < heap->capacity) {
        strcpy(heap->nodes[heap->size].data, data);
        heap->nodes[heap->size].freq = freq;
        heap->size++;
        //heap->nodes[heap->size++] = (heap_node){.data = data, .freq = freq};
        // Sort the min heap
        qsort(heap->nodes, heap->size, sizeof(heap_node), heap_node_compare);
    } 
    // Replace root if current freq is greater
    else if (freq > heap->nodes[0].freq) {
        strcpy(heap->nodes[0].data, data);
        heap->nodes[0].freq = freq;
        //heap->size++;
        //heap->nodes[0] = (heap_node){.data = *data, .freq = freq};
        qsort(heap->nodes, heap->size, sizeof(heap_node), heap_node_compare);
    }
} 

// free the heap
void free_min_heap(min_heap* heap) {
    if (heap) {
        free(heap->nodes);
        free(heap);
    }
}
