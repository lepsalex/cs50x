/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap by a factor of x (possitive int less than or equal to 100)
 *
 * Author: Alex Lepsa
 * Date: November 29, 2015
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// Inital values struct
struct values
{
    int width;
    int height;
    int padding;
    int length; 
};

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile n\n");
        return 1;
    }

    // Gets all arguments
    int sfactor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // ensure integer is between 1 and 100
    if ((sfactor < 1) || (sfactor > 100))
    {
        printf("Usage: Factor must be between 1 - 100 inclusive\n");
        return 2; 
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // determine original padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Store init values
    struct values init;
    init.width = bi.biWidth;
    init.height = bi.biHeight;
    init.padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    init.length = (bi.biWidth * 3) + padding;
    
    // Resize width and height
    bi.biWidth *= sfactor;
    bi.biHeight *= sfactor;
    
    // Update padding
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Update Image Size and File Size
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(init.height); i++)
    {
        // iterate over pixels in scanline (do this once for every sfactor)
        for (int j = 0; j < sfactor; j++)
        {
        
            // Move back
            fseek(inptr, 54 + init.length * i, SEEK_SET);
            
            for (int k = 0; k < init.width; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile (do this once for every sfactor)
                for (int l = 0; l < sfactor; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // Add padding
            for (int ii = 0; ii < padding; ii++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
