// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Global variables
int wordCount = 0;     // We use this to keep track of the number of words in the given dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int NUM_BUCKETS = 65536;

// Hash table
node *table[NUM_BUCKETS] = {NULL};

/* Returns true if word is in dictionary else false
 * TODO:
 * 1. Hash word to obtain hash value -> DONE
 * 2. Access linked list at that index in the hash table -> DONE
 * 3. Traverse linked list, looking for the word -> DONE
 */
bool check(const char *word)
{
    int length = strlen(word);
    char copy[length + 1];
    copy[length] = '\0';

    // Change all characters to lower case
    for (int i = 0; i < length; i++)
    {
        copy[i] = tolower(word[i]);
    }

    // Hash word to obtain hash value
    int index = hash(copy) % NUM_BUCKETS;

    // Access linked list at that index in the hash table
    node *cursor = table[index];

    // Traverse linked list, looking for the word
    while (cursor != NULL)
    {
        if (strcmp(copy, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor-> next;
    }

    return false;

}

/* Hashes word to a number
 * As stated in the PSET5 "specifications"
 * "You may search for (good) hash functions online, so long as you cite the origin of any hash function you integrate into your own code"
 * I am allowed to use a hash function that I found online, I use the following one.
 *
 * Hash function by "yangrq1018", code taken from https://gist.github.com/yangrq1018
 * Edited by me, to fit "dictionary.h"
 */
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % NUM_BUCKETS;
}

/* Loads dictionary into memory, returning true if successful else false
 * TODO:
 * 1. Open dictionary -> DONE
 * 2. Read strings from file one at a time -> DONE
 * 3. Create a new node for each word -> DONE
 * 4. Hash word to obtain a hash value -> Done
 * 5. Insert node into hash table at that location -> DONE
 */
bool load(const char *dictionary)
{
    char wordBuffer[LENGTH + 1];

    // Open dictionary and error checking
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("ERROR: Loading dictionary failed\n");
        return false;
    }

    // Read strings from file one at a time
    while (fscanf(fp, "%s", wordBuffer) != EOF)
    {
        // Create new node for each word and error checking
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("ERROR: Not enough memory available (Load)");
            unload();   // Unload dictionary from memory
            return false;
        }

        // Copy word into the new node
        strcpy(newNode->word, wordBuffer);

        // Hash word to obtain a hash value
        // Index = the spot where we need to insert the new node
        int index = hash(wordBuffer);

        // Insert node into hash table at that location
        newNode->next = table[index];
        table[index] = newNode;

        // Used for the "size()" function to return the total number of words in a dictionary
        wordCount++;
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        node *next = table[i];
        while (next != NULL)
        {
            node *temp = next;
            next = next-> next;
            free(temp);
        }
    }

    wordCount = 0;
    return true;
}
