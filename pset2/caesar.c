/**
*   Author: Alex Lepsa
*   Title: Problem Set 2 - caesar.c
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
    
    // Convert command line string number to int
    int k = atoi(argv[1]);
    
    // If k is not a possitive int, return 1 (error)
    if (k < 1)
    {
        printf("Key must be a non-negative integer!\n");
        return 1;
    }
    
    // Get message to encrpy from the user
    string message = GetString();
    
    // Check to ensure string is not NULL
    if (message != NULL)
    {
    
        // Loop through the message string (array of chars) from start to finish
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            // Only dealing with alphabetical characters
            if (isalpha(message[i]))
            {
             
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
            }
        }
        
        // Print the encrypted message
        printf("%s\n", message);
        
        // Explictly return 0 (success)
        return 0;
    }
}
