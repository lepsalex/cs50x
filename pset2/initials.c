/**
*   Author: Alex Lepsa
*   Title: Problem Set 2 - initials.c
*   Date: Monday, November 7, 2015
*/

#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = GetString();
    
    if (name != NULL)
    {        
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            name[i] = toupper(name[i]);
            
            if (i == 0)
            {
                printf("%c", name[i]);
            }
            else if (name[i - 1] == ' ')
            {
                printf("%c", name[i]);
            }
            else if (i == n - 1)
            {
                printf("\n");
            }
        }
    }
}
