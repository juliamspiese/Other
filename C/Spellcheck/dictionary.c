// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char word)
{
    return tolower(word) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        unsigned int bucket;
        int i = strlen(word);
        if (i != 1)
        {
            bucket = ((hash(word[0]) * 26) + hash(word[1]));
        }
        else
        {
            bucket = (hash(word[0]) * 26);
        }

        int j = sizeof(node);
        node *tmp = malloc(j);
        if(!tmp)
        {
            unload();
            return false;
        }

        strcpy(tmp->word, word);
        tmp->next = hashtable[bucket];
        hashtable[bucket] = tmp;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int n = 0;
    for (int bucket = 0; bucket < N; bucket++)
    {
        for (node *ptr = hashtable[bucket]; ptr != NULL; ptr = ptr->next)
        {
            n++;
        }
    }
    return n;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int bucket;
    int l = strlen(word);
    if (l != 1)
    {
        bucket = ((hash(word[0]) * 26) + hash(word[1]));
    }
    else
    {
        bucket = (hash(word[0]) * 26);
    }

    char word_tolower[LENGTH + 1];

    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        word_tolower[i] = tolower(word[i]);
    }
    word_tolower[n] = '\0';

    for (node *tmp = hashtable[bucket]; tmp != NULL; tmp = tmp->next)
    {
        int j = strcmp(tmp->word, word_tolower);
        if (!j)
        {
            return true;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = hashtable[i];
        while (ptr)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
