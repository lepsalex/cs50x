/**
*   Author: Alex Lepsa
*   Title: Week 1 Problem - Credit (hacker edition)
*   Date: Monday, August 3rd, 2015
*/

#include <string.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare top scope variables
    long long user_cc;
    
    printf("Please enter your credit card number: ");
    
    // get the credit card number as a long
    user_cc = GetLongLong();
    
    /* 
        NEED 1: To count number of digits to identify type
        NEED 2: Extract first couple digits to identify MC/Visa
        NEED 3: Convert long long to string
    */
    
    while (user_cc > 0)
    {
        int digit = user_cc % 10;
        
        printf("%i", digit);
            
        user_cc /= 100;
    }
    printf("\n");;
}
