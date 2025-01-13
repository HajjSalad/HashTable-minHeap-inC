//*****************************************************************************

//  main.c  -   main flow and entry point of the program

//*****************************************************************************

#include "hash_table.h"
#include <stdio.h>

//*****************************************************************************

int main() {

    int n;                                      // n most frequent words
    char path[] = "shakespeare.txt";            // Initialize the path

    printf("Enter the number of most frequent words to find: ");
    scanf("%d", &n);                            // Read the number of most frequent words

    find_frequent_words(path, n);               // return a pointer to a pointer

    return 0;
}