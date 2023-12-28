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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 2500;

// Hash table
node *table[N];

//WordCount for dictonary
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hashVal of the input text word
    int hashVal = hash(word);

    // Access linked list at the hashVal in hash table
    node *cursor = table[hashVal];

    // Traverse linked list, looking for the word
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        cursor = cursor -> next;
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    int startHash = 42069; //Funny number
    int finalHash;

    // My best attempt to create huge unique number, > N, for a given word.
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        startHash = startHash * toupper(word[i]);
        startHash -= tolower(word[i]);
    }

    // Walkthrough: If hash > N, return hash % N.
    finalHash = startHash % N;

    return finalHash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open Dictonary file
    FILE *dictOpen = fopen(dictionary, "r");

    if (dictOpen == NULL)
    {
        return false;
    }

    char *word = malloc(sizeof(char) * (LENGTH + 1));

    // Read strings from file one at a time
    while (fscanf(dictOpen, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *newNode = malloc(sizeof(node));

        // Copying word into newNode's word
        strcpy(newNode -> word, word);

        // Keeping count of word
        wordCount++;

        // Hash word to obtain a hash value
        int hashReturn = hash(newNode -> word);

        // Insert node into hash table at that location
        newNode -> next = table[hashReturn];
        table[hashReturn] = newNode;
    }

    free(word);
    fclose(dictOpen);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = table[0];
    node *temp;
    // Iterating hash table table
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        // Freeing each node
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
}