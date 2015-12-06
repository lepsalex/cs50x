/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 *
 * Updated: December 5th, 2015
 * Author: Alex Lepsa
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"

// Define some constants
#define ALPHA_SIZE  27
#define ASC_OFFSET  65
#define MAX_SIZE 47

// Declare Node Struct (tries data structure)
typedef struct node
{
    bool is_word;
    struct node* children[ALPHA_SIZE];
}
node;

// Declare root variable (accessible by all)
struct node* root = NULL;

// Word Variables (accessible by all)
char word[MAX_SIZE];
unsigned int word_count = 0;

// Create Node Function
node* createNode (void)
{
    return (node*) malloc(sizeof(node));
}

// Function that converts upper and lower-case letter to 0-25 values and ' to 26
unsigned int convert (unsigned int c)
{
    if (c == '\'')
    {
        // A = 0, Z = 25 so ... ' = 26
        c = 26;
    }
    else if (c != '\0' || c != '\n')
    {
        c = (toupper(c)) - 'A';
    }
    return c;
}

// Trie Insert Function
void trieInsert(node* ptr, char* word, unsigned int cursor)
{    
    // Get the char in word at position of cursor
    unsigned int c = word[cursor];
    
    // If c is the newline character call set is_word to true
    if (c == '\n')
    {
        ptr->is_word = true;
        word_count++;
    }
    else if (c != '\0')
    {
        // Convert char to number value (0-26)
        c = convert(c);
        
        // Increment cursor to next position
        cursor++;
        
        // If there is no pointer, allocate one, then go there ...
        if (ptr->children[c] == NULL)
        {
            ptr->children[c] = createNode();
            
            // Set Children to NULL
            for (int i = 0; i < ALPHA_SIZE; i++)
                ptr->children[c]->children[i] = NULL;
                
            // Set is_word to false
            ptr->children[c]->is_word = false;
                
            trieInsert(ptr->children[c], word, cursor);
        }
        
        // Else if there is a pointer assigned already go there and in word and cursor
        else
        {
           trieInsert(ptr->children[c], word, cursor);
        }  
    }
}

// Trie Unload Function
void trieUnload(node* ptr)
{
    // Loop through each child until we get to bottom
    for (int i = 0; i < ALPHA_SIZE; i++)
    {
        if(ptr->children[i] != NULL)
            trieUnload(ptr->children[i]);
    }
    
    // Free this ptr once done freeing all children
    free(ptr);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* next = root;
    unsigned int c = word[0];
    unsigned int i = 0;
    
    while (c != '\0')
    {    
        // convert to uppercase
        c = convert(c);
        
        // If null then no word so false
        if (next->children[c] == NULL)
        {
            return false;
        }
        
        // If not null advance to next node
        else
        {
            next = next->children[c];
        }
        
        i++;
        c = word[i];
    }
    
    // Return final value once at end of word
    return next->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // Open the dictionary file, exit if Null
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    
    // Create Root Node
    root = createNode();
    
    // Set Children to NULL
    for (int i = 0; i < ALPHA_SIZE; i++)
        root->children[i] = NULL;
        
    // Set is_word to false
    root->is_word = false;
        
    // Read file in word by word    
    while (fgets(word, sizeof(word), file) != NULL)
    {
        if (sizeof(word) > MAX_SIZE)
        {
            printf("Error, word in dictionary is longer than maximum allowed length of %d\n", MAX_SIZE - 2);
            return false;
        }
        else
        {
            trieInsert(root, word, 0);
        }
    }
    
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    trieUnload(root);
    return true;
}
