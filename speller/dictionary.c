// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

//Define an array of characters
char alphabets[] = "abcdefghijklmnopqrstuvwxyz\'";

//global varibale that stores the dictionary size (Number of words)
unsigned int num_of_words = 0;

void addWord(int *positions, int wordLength)
{
    node *trav = root;

    //iterate through the array of alphabetical positions of characters in a word
    for (int i = 0; i < wordLength; i++)
    {
        //if the char to be added is already in the trie, then go along the path
        if (trav->children[positions[i]])
        {
            trav = trav->children[positions[i]];
            continue;
        }

        //if the char is not already in the tire, then create a new node
        node *newNode = malloc(sizeof(node));
        newNode->is_word = false;
        for (int j = 0; j < N; j++)
        {
            newNode->children[j] = NULL;
        }

        //Assign the node pointer to the new node at the char position in the pointers array.
        trav->children[positions[i]] = newNode;

        //forward the trav pointer
        trav = trav->children[positions[i]];

    }
    //Mark the end of the word by setting the is_word flag true.
    trav->is_word = true;
}

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

    //poinetr for a character in the word
    char *charPtr;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        //TODO
        int wordLength = strlen(word);

        //create an array to store the respective indices of characters in a word
        int pos[wordLength];

        //iterate through the word and get the indices of characters.
        for (int i = 0; word[i]; i++)
        {
            //Get thepPointer to the character of a word in the alphabets array.
            charPtr = strchr(alphabets, word[i]);

            //index of the character in the alphabets array
            pos[i] = (int)(charPtr - alphabets);
        }

        //Add the word to the trie
        addWord(pos, wordLength);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

unsigned int find_size_recursively(node *trav)
{
    // Traverse through the entire array of node-poinetrs
    for (int i = 0; i < N; i++)
    {
        //If the node corrosponding to the character position is not null, then go to the leaf node in that path using recursion
        if (trav->children[i])
        {
            find_size_recursively(trav->children[i]);
        }
    }

    //If the end node is a valid word, increment the count of words.
    if (trav->is_word)
    {
        num_of_words++;

    }
    return num_of_words;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    num_of_words = 0;
    node *trav = root;

    //If the trie is empty
    if (trav == NULL)
    {
        return 0;
    }

    find_size_recursively(root);
    return num_of_words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *trav = root;
    char *charPtr;

    //Iterate through the word
    for (int i = 0; i < strlen(word); i++)
    {
        // Get thepPointer to the character of a word in the alphabets array.
        charPtr = strchr(alphabets, tolower(word[i]));

        //index of the character in the alphabets array
        int pos = (int)(charPtr - alphabets);

        // If the character-position is found in the trie, then follow along the path and check the subsequent charaters of the word
        if (trav->children[pos])
        {
            trav = trav->children[pos];
            continue;
        }

        //If a character is not found then, the word is not in the dictionary
        return false;
    }

    //At the end of the word, check if it is a valid word in the dictionary
    if (trav->is_word)
    {
        return true;
    }

    return false;
}

bool freeNodes(node *trav)
{
    //Free the nodes recursively by going to the leaf node and backtracking towards the root and lastly freeing the root
    for (int i = 0; i < N; i++)
    {
        if (trav->children[i])
        {
            freeNodes(trav->children[i]);
        }
    }
    free(trav);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *trav = root;

    if (trav == NULL)
    {
        return false;
    }

    //Call a recursive function to free the nodes
    return freeNodes(trav);
    // return false;
}
