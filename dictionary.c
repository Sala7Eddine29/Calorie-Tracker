// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
// The video uses 26 for simplicity (one for each letter)
const unsigned int N = 26;

// Hash table
node *table[N];

// Global variable to keep track of dictionary size
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Obtain hash value for the word
    int hash_value = hash(word);

    // Access linked list at that index in hash table
    node *cursor = table[hash_value];

    // Traverse linked list, looking for the word (case-insensitively)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Simple hash function: returns index based on first letter
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Error while opening dictionary file\n");
        return false;
    }

    // Buffer for each word
    char buffer[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(dict_file, "%s", buffer) != EOF)
    {
        // Create a new node for each word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(new_word->word, buffer);

        // Obtain hash value
        int hash_value = hash(buffer);

        // Insert node into hash table at that location
        new_word->next = table[hash_value];
        table[hash_value] = new_word;

        // Increment word counter
        word_counter++;
    }

    // Close dictionary file
    fclose(dict_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set pointers to the head of the list
        node *cursor = table[i];
        node *temp = cursor;

        // Traverse list and free nodes
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }

    return true;
}
