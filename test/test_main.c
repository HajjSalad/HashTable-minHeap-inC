//*****************************************************************************

//  test_main.c  -   main flow and entry point for the unit test

//*****************************************************************************

#include "hash_table.h"
#include "min_heap.h"
#include <stdio.h>

//*****************************************************************************

// Hash table
void test_hash();
void test_init_hash_table();
void test_hash_table_insert();
void test_hash_table_lookup();
void test_hash_table_expand(); 

// Min heap
void test_init_min_heap();
void test_min_heap_insert();

//*****************************************************************************

int main(){

    printf("\nRunning tests...\n\n");

    // Hash table
    test_hash();
    test_init_hash_table();
    test_hash_table_insert();
    test_hash_table_lookup();
    test_hash_table_expand(); 

    // Min heap
    test_init_min_heap();
    test_min_heap_insert();

    printf("\nAll tests passed successfully.\n\n");

    return 0;
}