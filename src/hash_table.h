//*****************************************************************************

//  hash_table.h  -   Hash Table header file

//*****************************************************************************

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdbool.h>

#define INITIAL_CAPACITY    10
#define MAX_WORD            256

//*****************************************************************************

typedef struct {                    // Word structure
    char data[MAX_WORD];
    int freq;
} word;

word *hash_table[TABLE_SIZE];       // Declare the hash Table

int *table_capacity;                // Capacity of the hash Table

//*****************************************************************************

// Function declaration for hash table 
unsigned long hash(unsigned char *str);
void init_hash_table();
bool hash_table_insert(word* w);
word* hash_table_lookup(char* lookWord);

#endif
//*****************************************************************************