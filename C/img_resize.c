// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //remember resize factor
    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //storing sizeof(RGBTRIPLE) in integer variable
    int s = sizeof(RGBTRIPLE);

    //makes sure first argument is a positive integer between 1 and 100
    if (n < 1 || n > 100)
    {
        printf("Usage: enter valid resize factor\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }

    //storing old dimensions and padding as integers
    int in_biWidth = bi.biWidth;
    int in_biHeight = bi.biHeight;
    int in_padding = (4 - (bi.biWidth * s) % 4) % 4;

    //updates new dimensions and padding
    bi.biWidth *= n;
    bi.biHeight *= n;
    int out_padding = (4 - (bi.biWidth * s) % 4) % 4;

    //Assigning image and file size with resized width and height (by me)
    bi.biSizeImage = ((s * bi.biWidth) + out_padding) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_biHeight); i < biHeight; i++)
    {
        for(int row_tracker = 0; row_tracker < n; row_tracker++)
        {
        // iterate over pixels in scanline
            for (int j = 0; j < in_biWidth; j++)
            {
                for(int px_tracker = 0; px_tracker < n; px_tracker++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, s, 1, inptr);

                    // write RGB triple to outfile
                    fwrite(&triple, s, 1, outptr);

                    // moves pointer back one pixel if not at last pixel in row
                    if(px_tracker != (n - 1))
                    {
                        fseek(inptr, -s, SEEK_CUR);
                    }
                }
            }

            // skip over infile's padding, if any
            fseek(inptr, in_padding, SEEK_CUR);

            // then add outfile's padding
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }

            // moves pointer back to start of row if not at last row
            if(row_tracker != (n - 1))
            {
                fseek(inptr, (-s * in_biWidth) - in_padding, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
