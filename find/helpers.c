/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 *
 * Last Updated: November, 28th, 2015
 * Last Update Author: Alex Lepsa
 */
       
#include <cs50.h>

#include "helpers.h"

// Temp for test
#include <stdio.h>

/**
 * Binary Search to be called by search
 */
bool binary(int value, int values[], int high, int low)
{
    // If we are down to the last value to check
    if (high-low == 0)
    {
        // Check last element
        if (values[high] == value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    // Find midpoint of array
    int middle = (high + low) / 2;
    
    // Check if value is in middle (can happen)
    if (value == values[middle])
        return true;
    
    // Search high
    if (value > values[middle])
    {
        // Return binary again (high remains high point, low is now middle + 1)
        return binary(value, values, high, middle + 1);
    }
    // Search low
    else if (value < values[middle])
    {
        // Return binary again (high is now middle, low remains low)
        return binary(value, values, middle, low);
    }
    
    // Default return to false
    return false;
}
 
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Call our recursive binary search function above by returning its value :)
    return binary(value, values, n-1, 0);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Declare swap variable (temp)
    int temp;
    
    // Declare counter variable
    int counter;
    
    // Repeat the following until no swaps are made (counter is equal to 0)
    do
    {
        // Reset counter to 0
        counter = 0;
        
        for (int i = 0; i < n-1; i++)
        {
        
            // Check if value of [i] is greater than [i+1]
            if (values[i] > values[i+1])
            {
                // Assign value in [i] to temp
                temp = values[i];
                
                // Assign the lower value to value[i]
                values[i] = values[i+1];
                
                // Assign the higher value stored in temp to value[i+1]
                values[i+1] = temp;
                
                // Increment the counter to indicate that a swap has taken place
                counter++;
            }
        }
    }
    while (counter != 0);
}
