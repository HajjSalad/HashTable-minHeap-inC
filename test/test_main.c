//*****************************************************************************

//  test_main.c  -   main flow and entry point for the unit test

//*****************************************************************************

#include "hash_table.h"
#include <stdio.h>

//*****************************************************************************

void test_hash();
void test_init_hash_table();
void test_hash_table_insert();
void test_hash_table_lookup();
void test_hash_table_expand();

//*****************************************************************************

int main(){

    printf("\nRunning tests...\n\n");

    test_hash();
    test_init_hash_table();
    test_hash_table_insert();
    test_hash_table_lookup();
    test_hash_table_expand();

    printf("\nAll tests passed successfully.\n\n");

    return 0;
}