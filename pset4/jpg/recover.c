/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 *
 * Author: Alex Lepsa
 * Date: November 29, 2015
 */
 
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(void)
{
    // Open file
    FILE* file = fopen("card.raw", "r");
    
    // Check to ensure not NULL
    if (file == NULL)
    {
        fclose(file);
        printf("NULL Error\n");
        return 1;
    }
    
    // Create buffer (512 bytes)
    BYTE buffer[512];
    
    // Create temp file for jpg output
    FILE* temp = NULL;
    
    // Declare counter integer (used to number recovered files)
    int rfilenum = 0;
    
    // Recovered filename in 3-digit number format
    char rfilename[10];
    
    // Loop to EOF (end-of-file)
    while (!feof(file))
    {
        // Check for JPEG sequence
        if (buffer[0] == 0xff && buffer [1] == 0xd8 && buffer [2] == 0xff && ((buffer [3] == 0xe0) || (buffer[3] == 0xe1)))
        {
            // Check that temp file is NULL
            if (temp != NULL)
                fclose(temp);
                
            // Give the recovered file the correct name
            sprintf(rfilename, "%03d.jpg", rfilenum);
            
            // Open next file for write
            temp = fopen(rfilename, "w");
            
            // Write buffer to new file
            fwrite(buffer, sizeof(buffer), 1, temp);
            
            // Increment Counter
            rfilenum++;
        }
        else if (rfilenum > 0)
        {
            // Write current buffer to temp file
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        
        // Read buffer-sized part of file to buffer
        fread(buffer, sizeof(buffer), 1, file);
    }
    
    // Close file
    fclose(file);
    
    // Return
    return 0;
}
