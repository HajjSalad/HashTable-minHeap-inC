//*****************************************************************************

//  hash_table.h  -   Hash Table header file

//*****************************************************************************

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY        10
#define MAX_WORD                256

//*****************************************************************************************

typedef struct {                    // Word structure - hash table entry
    char data[MAX_WORD];
    size_t freq;
} word;

typedef struct {                    // hashTable structure 
    word* entries;                  // a pointer to the first element 
    size_t capacity;                // total number of slots in the hash table
    size_t length;                  // total number of actual items in the hash table
} hashTable;  

//*****************************************************************************************

// Function declaration for hash table 
unsigned long hash(unsigned char *str);
hashTable* init_hash_table();
void free_hash_table(hashTable* table);
void free_hash_table(hashTable* table);
bool hash_table_insert(hashTable* table, word* w);
void* hash_table_lookup(hashTable* table, char* lookWord);

#endif
//*****************************************************************************************