// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

int words = 0;

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
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
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
        int index = hash(word);
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->next = NULL;

        n->next = hashtable[index];
        hashtable[index] = n;
        words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Returns true if word is in dictionary else false

bool compare(char word1[LENGTH + 1], const char word2[LENGTH + 1])
{
    for (int i = 0; word1[i] != '\0' || word2[i] != '\0'; i++)
    {
        if (tolower(word1[i]) != tolower(word2[i]))
        {
            return false;
        }
    }
    return true;
}

bool check(const char *word)
{
    unsigned int index = hash(&word[0]);

    node *temp;
    temp = hashtable[index];
    while (temp != NULL)
    {
        if (compare(temp->word, word)){
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *temp;
        while (hashtable[i] != NULL)
        {
            temp = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            free(temp);
        }
    }
    return true;
}
