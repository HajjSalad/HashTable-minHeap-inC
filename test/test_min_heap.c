//*****************************************************************************

//  test_min_heap.c  -   Hash Table implementation

//*****************************************************************************

#include "min_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//*****************************************************************************

void test_init_min_heap() {
    size_t n = 5;               // Capacity of min heap

    min_heap* heap = init_min_heap(n);
    if(heap == NULL) {
        fprintf(stderr, "init_min_heap returned NULL");
        return;
    }

    // Check all the elements of the nodes
    for (size_t i=0; i<heap->capacity; i++) {
        assert(heap->nodes[i].data[0] == '\0');
        assert(heap->nodes[i].freq == 0);
    }

    // Check the min heap features
    assert(heap->size == 0);
    assert(heap->capacity == n);

    printf("test_init_min_heap passed.\n");

    free_min_heap(heap);
}

void test_min_heap_insert() {
    size_t n = 6;    // Capacity of min heap
    min_heap* heap = init_min_heap(n);
    
    assert(heap != NULL);

    // Imagine a complete binary tree with six nodes and 0 at root
    // Each node string corresponds with the number value
    char* text1[] = {"four", "one", "five", "zero" , "three", "two"};
    size_t freq[] = {4, 1, 5, 0, 3, 2};

    // Insert elements into the heap
    for (size_t i=0; i<n; i++) {
        min_heap_insert(heap, text1[i], freq[i]);
    }

    char* text2[] = {"zero", "one", "two", "three", "four", "five"};
    for (size_t i=0; i<n; i++) {
        assert(strncmp(heap->nodes[i].data, text2[i], MAX_WORD) == 0);
    }

    free_min_heap(heap);

    printf("test_min_heap_insert passed.\n");
}