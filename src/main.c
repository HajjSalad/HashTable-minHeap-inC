//***********************************************************************************************

//  main.c  -   main flow and entry point of the program

//***********************************************************************************************

#include "hash_table.h"
#include "min_heap.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//***********************************************************************************************

// Fucntion Declaration
void print_head(hashTable* table);
void word_lookup(hashTable* table, char* lookup);
void clean_word(char *current_word);
void find_n_most_frequent(hashTable* table, min_heap* heap, size_t n);

//**********************************************************************************************

// Task 1: Print head of the dataset.
void print_head(hashTable* table) {

    size_t counter = 0;
    // Print the first 10 words and their frequency
    printf("\tWord\t\tFreq\n");
    for (size_t i=0; i<table->capacity; i++) {
        if (table->entries[i].data[0] != '\0') {
            // Print word and frequency
            printf("\t%s\t\t%zu\n", table->entries[i].data, table->entries[i].freq);
            counter++;
            if (counter == 10) {        // Stop after 10 entries
                break;
            }
        }
    }
}

// Task 2: Find the n most frequent words in the dataset
void find_n_most_frequent(hashTable* table, min_heap* heap,  size_t n) {

    for (size_t i=0; i<table->capacity; i++) {
        if (table->entries[i].data[0] != '\0') {
            min_heap_insert(heap, table->entries[i].data, table->entries[i].freq);
        }
    }

    // Print the n words
    printf("\tWord\t\t\tFreq\n");
    for (size_t i=0; i<n; i++) {
        printf("\t%s\t\t\t%zu\n", heap->nodes[i].data, heap->nodes[i].freq);
    }
}

// Task 3: Lookup if word mentioned in dataset. Return word and frequency.
void word_lookup(hashTable* table, char* lookup) {

    // Look up in the hash table
    word* foundWord = hash_table_lookup(table, lookup);

    if (foundWord == NULL) {            // if empty
        printf("Word not found!\n");
    } else {
        printf("Word found: %s freq:%zu\n", foundWord->data, foundWord->freq);
    }
}

// Clean punctuations from a word
void clean_word(char *current_word) {
    char *src = current_word, *dst = current_word;

    while(*src) {
        if(isalnum((unsigned char)*src)) {      // Copy only alphanumeric characters
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';    // Null-terminate the clean string
}

//**********************************************************************************************

int main() {

    size_t n;
    char path[] = "src/test.txt";            
    FILE *fp = NULL;
    char current_word[MAX_WORD];                        // Buffer to store the word

    // Open file in read mode
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    hashTable* table = init_hash_table();               // Initialize hash table
    
                        
    while(fscanf(fp, "%255s", current_word) == 1){      // Read upto 255 characters
        clean_word(current_word);                       // Remove punctuations
        if(strlen(current_word) > 0) {                  // Ensure word not empty after cleaning
            hash_table_insert(table, current_word);    // Insert the word into the hash table
        }
    }

    // Start of Program
    printf("\n\t* Start of Program *\n");
    
    while(1) {
        printf("Choose a task please:\n");
        printf("Task 1: Print head of the dataset.\n");
        printf("Task 2: Find the n most frequent words in the dataset.\n");
        printf("Task 3: Lookup if word mentioned in dataset. Returns word and frequency.\n");
        printf("Enter 1 or 2 or 3: ");

        size_t select, n;
        char lookup[MAX_WORD]; 
        scanf("%zu", &select);              // Get task selection

        if (select == 1) {                  // Task 1
            print_head(table);
        } else if (select == 2) {           // Task 2  
            printf("Enter the n: ");
            scanf("%zu", &n);
            min_heap* heap = init_min_heap(n);
            find_n_most_frequent(table, heap, n);
            free(heap);
        } else if (select == 3) {           // Task 3
            printf("Enter the word you'd like to look up: ");
            scanf("%255s", lookup);
            word_lookup(table, lookup);
        } else {
            printf("\nInvalid input. Enter 1 or 2 or 3");
        }
        printf("\n");
    }

    free(table);
    fp = NULL;
    
    return 0;
}
//**********************************************************************************************