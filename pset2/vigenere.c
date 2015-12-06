/**
*   Author: Alex Lepsa
*   Title: Problem Set 2 - vigenere.c
*   Date: Monday, November 7, 2015
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{

    // Ensure that the user has entered only one single command line argument
    if (argc != 2)
    {
        printf("ERROR\n");
        return 1;
    }
    
    string key = argv[1];
    
    // If any char in key is not alphabetical, return 1 (error)
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Key must be entirely alphabetical (no numbers or special characters!)\n");
            return 1;
        }
        
        // Transform key to all uppercase
        key[i] = toupper(key[i]);
    }    
    
    // Get message to encrpy from the user
    string message = GetString();
    
    // Check to ensure string is not NULL
    if (message != NULL)
    {
    
        // Set key position (kpos) to 0
        int kpos = 0;
    
        // Loop through the message string (array of chars) from start to finish
        for (int i = 0, n = strlen(message); i < n; i++)
        {
                    
            // Only dealing with alphabetical characters
            if (isalpha(message[i]))
            {
            
                // If kpos is greater than length of key then reset
                if (kpos >= strlen(key))
                {
                    kpos = 0;
                }
                
                // Set shift by 0-indexing key[keypos]
                int k = key[kpos] - 65;
             
                // If uppercase char
                if (isupper(message[i]))
                {
                    int p = (int) message[i] - 65; // Convert to 0-index
                    int c = ((p + k) % 26) + 65; // Apply Caesar formula and the index back to ASCII
                    message[i] = c; // Save over char in array
                }
                
                // If lowercase char
                if (islower(message[i]))
                {
                    int p = (int) message[i] - 97;
                    int c = ((p + k) % 26) + 97;
                    message[i] = c;
                }
                
                // Increment kpos by 1
                kpos++;
            }
        }
        
        // Print the encrypted message
        printf("%s\n", message);
        
        // Explictly return 0 (success)
        return 0;
    }
}
