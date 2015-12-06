/**
*   Author: Alex Lepsa
*   Title: Problem Set 1 - greedy.c
*   Date: Monday, August 8, 2015
*/

#include <math.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float change;
    
    // Get input from user until valid (not less than 0)
    do
    {
        printf("How much change is owed?\n$");
        change = GetFloat();
    }
    while (change < 0);
    
    /* Convert the change input (float) to cents (int)
     * and use roundf to normalize the float.
    */
    int cents = roundf(change * 100);
    
    // Initialize coin counter int
    int coins = 0;
    
    do
    {
    
        if (cents >= 25)
        {
            // Add the quotient to the coins variable
            coins += (cents / 25);
            
            // Reduce cents by the quotient * 25
            cents = cents - (25 * (cents / 25));
        }
        // Repeat for each coin
        else if ((cents < 25) && (cents >= 10))
        {
            coins += (cents / 10);
            cents = cents - (10 * (cents / 10));
        }
        else if ((cents < 10) && (cents >= 5))
        {
            coins += (cents / 5);
            cents = cents - (5 * (cents / 5));
        }
        else if ((cents < 5) && (cents >= 1))
        {
            coins += (cents / 1);
            cents = cents - (1 * (cents / 1));
        }
    }
    while (cents > 0);
    
    printf("%i\n", coins);
}
