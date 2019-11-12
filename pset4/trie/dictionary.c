// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

unsigned long int words = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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
    int index;
    node *pointer = root;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        for (int i = 0; i <= strlen(word); i++)
        {
            if (word[i] == '\'')
                index = 26;
            else
                index = tolower(word[i]) - 97;

            if (word[i] != '\0')
            {
                if(pointer->children[index] == NULL)
                    pointer->children[index] = malloc(sizeof(node));
                pointer = pointer->children[index];
            }
            else
            {
                pointer->is_word = true;
                words++;
                pointer = root;
            }
        }
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
bool check(const char *word)
{
    node *pointer = root;
    int index;
    for (int i = 0; i <= strlen(word); i++)
    {
        if (word[i] == '\'')
            index = 26;
        else
            index = tolower(word[i]) - 97;

        if (word[i] != '\0')
        {
            if (pointer->children[index] == NULL)
                return false;
            else
                pointer = pointer->children[index];
        }
        else
        {
            if (pointer->is_word == true)
                return true;
        }
    }
    return false;
}

void unloadnode()
{
    for (int i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
            unloadnode(root->children[i]);
    }
    free(root);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unloadnode();
    return true;
}


