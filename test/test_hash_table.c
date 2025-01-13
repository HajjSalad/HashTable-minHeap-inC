//*****************************************************************************

//  test_hash_table.c  -   unit test for Hash Table

//*****************************************************************************

#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//*****************************************************************************

void test_hash() {
    char str1[] = "word";
    int index1 = hash((unsigned char *)str1) % 10;                 // hash for range 1-10 
    assert(index1 >= 0 && index1 < 10);           // Ensure index is within range

    char str2[] = "word";
    int index2 = hash((unsigned char *)str2) % 10;     
    int index2_again = hash((unsigned char *)str2) % 10;             
    assert(index2 == index2_again);               // same string produce same hash       

    char str3[] = "";                             // empty string
    int index3 = hash((unsigned char *)str3) % 10;
    assert(index3 >= 0 && index3 < 10);

    char str4[] = "a";                            // single character
    int index4 = hash((unsigned char *)str4) % 10;
    assert(index4 >= 0 && index4 < 10);

    char str5[] = "aaaaaaaa";                     // repeated characters
    int index5 = hash((unsigned char *)str5) % 10;
    assert(index5 >= 0 && index5 < 10);

    char str6[] = "hello";                        // different string different hash - ignore collision
    char str7[] = "world";
    int index6 = hash((unsigned char *)str6) % 10;
    int index7= hash((unsigned char *)str7) % 10;
    assert(index6 != index7);

    printf("test_hash passed\n");
}

void test_init_hash_table() {
    init_hash_table();                  // Calling this initializes a hash table of size TABLE_SIZE

    for (int i=0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("Entry %d is NULL (allocation failed).\n", i);
        } else{
            assert(hash_table[i]->data[0] == '\0');                 // data = ""
            assert(hash_table[i]->freq == 0);                       // freq = 0
        }
    }
    printf("test_init_hash_table passed\n");

    // Free allocated memory
    for (int i=0; i<TABLE_SIZE; i++) {
        if(hash_table[i] != NULL){
            free(hash_table[i]);                    // Free memory allocated for each word struct
            hash_table[i] = NULL;                   // Set pointer to NULL for safety
        }
    }
}

void test_hash_table_insert() {
    word text1 = {
        .data = "hello",
        .freq = 0
    };
    init_hash_table();

    assert(hash_table_insert(&text1));                                          // Insert the word
    int index1 = hash((unsigned char *)text1.data) % TABLE_SIZE;
    assert(strncmp(hash_table[index1]->data, text1.data, MAX_WORD) == 0);       // Check word is stored
    assert(hash_table[index1]->freq == 1);                                      // Check freq set to 1

    word text2 = { .data = "hello", .freq = 0 };                                // text1 = text2
    assert(hash_table_insert(&text2));
    assert(hash_table[index1]->freq == 2);                                      // freq incremented to 2

    word text3 = { .data = "world", .freq = 0 };

    assert(hash_table_insert(&text3));                                          // Insert the word
    int index3 = hash((unsigned char *)text3.data) % TABLE_SIZE;
    assert(index3 != index1);                                                   // Ensure its a different slot
    assert(strncmp(hash_table[index3]->data, text3.data, MAX_WORD) == 0);       // Check word is stored

    printf("test_hash_table_insert passed\n");

    // Free allocated memory
    for (int i=0; i<TABLE_SIZE; i++) {
        if(hash_table[i] != NULL){
            free(hash_table[i]);                    // Free memory allocated for each word struct
            hash_table[i] = NULL;                   // Set pointer to NULL for safety
        }
    }
}

void test_hash_table_lookup() {
    word text1 = { .data = "hello", .freq = 0 };                     // Initialize test words
    word text2 = { .data = "world", .freq = 0 };
    word text3 = { .data = "dragon", .freq = 0 };
    init_hash_table();
    hash_table_insert(&text1);                                       // Insert the words
    hash_table_insert(&text2);
    hash_table_insert(&text3);

    char str1[] = "hello";
    word* foundWord1 = hash_table_lookup(str1);                      // lookup the words
    assert(foundWord1 != NULL);
    assert(strncmp(foundWord1->data, text1.data, MAX_WORD) == 0);     
    
    char str2[] = "world";
    word* foundWord2 = hash_table_lookup(str2);
    assert(foundWord2 != NULL);
    assert(strncmp(foundWord2->data, text2.data, MAX_WORD) == 0);     // verify the data

    char str3[] = "unknown";                                          // Lookup word not in table
    word* foundWord3 = hash_table_lookup(str3);
    assert(foundWord3 == NULL);                                       // return NULL for missing word

    printf("test_hash_table_lookup passed\n");

    // Free allocated memory
    for (int i=0; i<TABLE_SIZE; i++) {
        if(hash_table[i] != NULL){
            free(hash_table[i]);                    // Free memory allocated for each word struct
            hash_table[i] = NULL;                   // Set pointer to NULL for safety
        }
    }
}