/**
*   Author: Alex Lepsa
*   Title: Problem Set 1 - mario.c
*   Date: Monday, August 8, 2015
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int p_height;
    
    // Get input from user until valid (not less than 0 or greater than 23)
    do
    {
        printf("Height: ");
        p_height = GetInt();
    }
    while ((p_height < 0) || (p_height > 23));
    
    /* Parent Loop: First a loop that builds the number of rows equal to the
     *              user input (p_height).
     *
     * Nested Loop: A loop that goes through each row and the same amount of
     *              times that there are rows plus one additional time as we
     *              want to double up the last column.
     *
     * If/else:     This checks if the the column we are on is greater than
     *              or equal to the user defined height minus the row we're
     *              currently on minus one (for the double col), then if that
     *              condition is true it print's a hash to the screen otherwise
     *              it prints a space.
     *
     * Example:     One row 4 (3 in array) of an 8 row pyramid (9 char width):
     *
     *              First col: if ( 0 >= (8 - 0 - 1)) = false 0 is not > than 7
     *
     *              Fifth col: if ( 4 >= (8 - 3 - 1)) = true as 4 = 4 
    */
    for (int row = 0; row < p_height; row++)
    {
    
        for (int col = 0; col < (p_height + 1); col++)
        {
        
            if (col >= (p_height - row - 1))
            {
                // Print the hash
                printf("#");
            }
            else
            {
                // Print the space
                printf(" ");
            }
            
        }
        
        // Prints \n to drop the next row down a line
        printf("\n");
        
    } 
}
