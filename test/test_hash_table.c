//*****************************************************************************

//  test_hash_table.c  -   unit test for Hash Table

//*****************************************************************************

#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

//*****************************************************************************

void test_hash() {
    char str1[] = "word";
    size_t index1 = hash((unsigned char *)str1) % 10;       // hash for range 1-10 
    assert(index1 >= 0 && index1 < 10);                  // Ensure index is within range

    char str2[] = "word";
    size_t index2 = hash((unsigned char *)str2) % 10;     
    size_t index2_again = hash((unsigned char *)str2) % 10;             
    assert(index2 == index2_again);                     // same string produce same hash       

    char str3[] = "";                                   // empty string
    size_t index3 = hash((unsigned char *)str3) % 10;
    assert(index3 >= 0 && index3 < 10);

    char str4[] = "a";                                  // single character
    size_t index4 = hash((unsigned char *)str4) % 10;
    assert(index4 >= 0 && index4 < 10);

    char str5[] = "aaaaaaaa";                           // repeated characters
    size_t index5 = hash((unsigned char *)str5) % 10;
    assert(index5 >= 0 && index5 < 10);

    char str6[] = "hello";                             // different hash - ignore collision
    char str7[] = "world";
    size_t index6 = hash((unsigned char *)str6) % 10;
    size_t index7= hash((unsigned char *)str7) % 10;
    assert(index6 != index7);

    printf("test_hash passed\n");
}

void test_init_hash_table() {

    hashTable* table = init_hash_table();            // Initialize the hash table
    if (table == NULL) {
        fprintf(stderr, "init_hash_table returned NULL");
        return;
    }

    // Check all the elements of the entries
    for (size_t i=0; i<INITIAL_CAPACITY; i++) {
        assert(table->entries[i].data[0] == '\0');      // Check for empty string
        assert(table->entries[i].freq == 0);            // Check for freq = 0
    }

    // Check the hash table features
    assert(table->capacity == INITIAL_CAPACITY);
    assert(table->length == 0);

    printf("test_init_hash_table passed\n");

    // Free allocated memory
    free_hash_table(table);
}


void test_hash_table_insert() {
    word text1 = { .data = "hello", .freq = 0 };
    hashTable* table = init_hash_table();

    assert(hash_table_insert(table, &text1));                                          // Insert the word
    size_t index1 = hash((unsigned char *)text1.data) % table->capacity;
    assert(strncmp(table->entries[index1].data, text1.data, MAX_WORD) == 0);       // Check word is stored
    assert(table->entries[index1].freq == 1);                                      // Check freq set to 1

    word text2 = { .data = "hello", .freq = 0 };                                // text1 = text2
    assert(hash_table_insert(table, &text2));
    assert(table->entries[index1].freq == 2);                                      // freq incremented to 2

    word text3 = { .data = "world", .freq = 0 };

    assert(hash_table_insert(table, &text3));                                          // Insert the word
    size_t index3 = hash((unsigned char *)text3.data) % table->capacity;
    assert(index3 != index1);                                                   // Ensure its a different slot
    assert(strncmp(table->entries[index3].data, text3.data, MAX_WORD) == 0);       // Check word is stored

    printf("test_hash_table_insert passed\n");

    free_hash_table(table);
}

void test_hash_table_lookup() {
    word text1 = { .data = "hello", .freq = 0 };                     // Initialize test words
    word text2 = { .data = "world", .freq = 0 };
    word text3 = { .data = "dragon", .freq = 0 };

    hashTable* table = init_hash_table();
    hash_table_insert(table, &text1);                                // Insert the words
    hash_table_insert(table, &text2);
    hash_table_insert(table, &text3);

    char str1[] = "hello";
    word* foundWord1 = hash_table_lookup(table, str1);                      // lookup the words
    assert(foundWord1 != NULL);
    assert(strncmp(foundWord1->data, text1.data, MAX_WORD) == 0);     
    
    char str2[] = "world";
    word* foundWord2 = hash_table_lookup(table, str2);
    assert(foundWord2 != NULL);
    assert(strncmp(foundWord2->data, text2.data, MAX_WORD) == 0);     // verify the data

    char str3[] = "unknown";                                          // Lookup word not in table
    word* foundWord3 = hash_table_lookup(table, str3);
    assert(foundWord3 == NULL);                                       // return NULL for missing word

    printf("test_hash_table_lookup passed\n");

    free_hash_table(table);
}

void test_hash_table_expand() {
    hashTable* table = init_hash_table();

    // Insert elements to trigger expansion
    for (size_t i=0; i<table->capacity; i++) {
        word w;
        snprintf(w.data, MAX_WORD, "word%zu", i);            // Create unique words
        w.freq = 1;
        hash_table_insert(table, &w);   
    }

    size_t old_capacity = table->capacity;         
    bool expanded = hash_table_expand(table);               // Expand hash table
    if (!expanded) {
        fprintf(stderr, "Failed to expand hash table\n");
    }
    assert(expanded);
    assert(table->capacity == old_capacity * 2);   // Check old capacity is doubled

    // Verify priously inserted elements still in the table
    for (size_t i=0; i<old_capacity; i++) {
        char lookup_word[MAX_WORD];
        snprintf(lookup_word, MAX_WORD, "word%zu", i);
        word* found = hash_table_lookup(table, lookup_word);
        assert(found != NULL);          // Ensure word exists
        assert(strncmp(found->data, lookup_word, MAX_WORD) == 0);
    }

    printf("test_hash_table_expand passed.\n");

    free_hash_table(table);
}