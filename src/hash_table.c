//******************************************************************************************************

//  hash_table.c  -   Hash Table implementation

//******************************************************************************************************

#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

//******************************************************************************************************

// djb2 by Dan Bernstein
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;                   // Initial hash value - starting value
    size_t c;

    while ((c = *str++)) {                       // Iterate through each character in the string
        hash = ((hash << 5) + hash) + c;         // hash * 33 + c 
    }
    return hash;
}

// Initialize a new hash table and return a pointer to it
hashTable* init_hash_table(void) {

    // Allocate memory for the hash table
    hashTable* table = malloc(sizeof(hashTable));                // table - pointer of type hashTable
    if (table == NULL) {
        fprintf(stderr, "Memory alloc failed for hash table\n");     
        return NULL;
    }

    // Allocate memory for the entries array
    table->entries = calloc(INITIAL_CAPACITY, sizeof(word));
    if (table->entries == NULL) {
        fprintf(stderr, "Memory alloc failed for entries\n");
        free(table);   // Free the allocated memory for table
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->length = 0;

    for (size_t i=0; i<INITIAL_CAPACITY; i++) {
        table->entries[i].data[0] = '\0';
        table->entries[i].freq = 0;
    }

    return table;                                // return the pointer to the initialized hash table
}

// Free the hash table and its entries
void free_hash_table(hashTable* table) {
    if (table != NULL) {
        free(table->entries);             // Free the array of entries
        free(table);                      // Free the hash table itself
    }
}

/*
// Expand hash table if more than filled
bool hash_table_expand() {
    in
} */

// Return true if successful, false otherwise
bool hash_table_insert(hashTable* table, word* w) {
    if (table == NULL || w == NULL) return false;                // Validate the input params
    
    // Get the index for the word
    size_t index = hash((unsigned char *)w->data) % table->capacity;     

    // Handling collision and Check if already stored
    for (size_t i=0; i < table->capacity; i++) {
        size_t try_index = (i + index) % table->capacity;

        // If slot is empty, insert the word
        if (table->entries[try_index].data[0] == '\0') {
            strcpy(table->entries[try_index].data, w->data);
            table->entries[try_index].freq = 1;
            table->length++;                              // Increment the lenght of hash table
            return true;
        }
        // If slot contain same word, update frequency
        if (strncmp(table->entries[try_index].data, w->data, MAX_WORD) == 0) {
            table->entries[try_index].freq += 1;          // increment the frequency
            return true;
        }
    }
    // If no suitable slot found, return false
    return false;
}

void* hash_table_lookup(hashTable* table, char* lookWord) {
    if (table == NULL || lookWord == NULL || lookWord[0] == '\0') return NULL;     

    size_t index = hash((unsigned char *)lookWord) % table->capacity;

    // Search for the word
    for (size_t i=0; i < table->capacity; i++) {
        size_t try_index = (i + index) % table->capacity;
        
        // Check slot is occupied and word matches
        if (table->entries[try_index].data[0] != '\0') {        
            if(strncmp(table->entries[try_index].data, lookWord, MAX_WORD) == 0) {
                return (void*)&table->entries[try_index];               // Found the word
            }
        }
    }
    return NULL;                // Word not found
}

