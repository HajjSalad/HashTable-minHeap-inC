//*****************************************************************************

//  hash_table.c  -   Hash Table implementation

//*****************************************************************************

#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//*****************************************************************************

// djb2 by Dan Bernstein
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;                  // Initial hash value - starting value
    int c;

    while ((c = *str++)) {                        // Iterate through each character in the string
        hash = ((hash << 5) + hash) + c;        // hash * 33 + c 
    }
    return hash;
}

// Initialize the hash table
void init_hash_table() {
    int table_failure_count = 0;

    for (int i=0; i < TABLE_SIZE; i++) {
        hash_table[i] = (word*)malloc(sizeof(word));        // Allocate memory for each 'word' struct
        if (hash_table[i] == NULL) {                        // Allocation was unsuccessful
            fprintf(stderr, "Mem allocation failed for hash_table[%d]. Marking as NULL. \n", i);
            hash_table[i] = NULL;                           // Explicitly set failed slots to NULL
            table_failure_count++;
            continue;                                       // Skip initialization for this entry
        }
        // Allocation was successful
        hash_table[i]->data[0] = '\0';                     // Initialize with an empty string
        hash_table[i]->freq = 0;
    }
    if (table_failure_count > 0) {
        fprintf(stderr, "Initialization completed with %d failed entries.\n", table_failure_count);
    }
}

bool hash_table_expand() {
    
}

// Return true if successful, false otherwise
bool hash_table_insert(word* w) {
    if (w == NULL) return false;                            // There's nothing to insert
    
    int index = hash((unsigned char *)w->data) % TABLE_SIZE;             // Get the index for the word

    // Handling collision and Check if already stored
    for (int i=0; i < TABLE_SIZE; i++) {
        int try_index = (i + index) % TABLE_SIZE;

        if (hash_table[try_index] != NULL) {                // Not set to NULL during initialization 
            // If slot is empty, insert the word
            if (hash_table[try_index]->data[0] == '\0') {
                strcpy(hash_table[try_index]->data, w->data);
                hash_table[try_index]->freq = 1;
                return true;
            }
            if (strncmp(hash_table[try_index]->data, w->data, MAX_WORD) == 0) {
                // Word already exists
                hash_table[try_index]->freq += 1;          // increment the frequency
                return true;
            }
        }
    }
    // If no suitable slot found, return false
    return false;
}

word* hash_table_lookup(char* lookWord) {
    if (lookWord == NULL || lookWord[0] == '\0') return NULL;           // Invalid input

    int index = hash((unsigned char *)lookWord) % TABLE_SIZE;

    // Search for the word
    for (int i=0; i < TABLE_SIZE; i++) {
        int try_index = (i + index) % TABLE_SIZE;
        
        // Check slot is occupied and word matches
        if (hash_table[try_index] != NULL) {        
            if(strncmp(hash_table[try_index]->data, lookWord, MAX_WORD) == 0) {
                return hash_table[try_index];               // Found the word
            }
        }
    }
    return NULL;                // Word not found
}

