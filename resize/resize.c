// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

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

    BITMAPFILEHEADER bfIn, bfOut;
    BITMAPINFOHEADER biIn, biOut;

    // read infile's BITMAPFILEHEADER
    fread(&bfIn, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    fread(&biIn, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bfIn.bfType != 0x4d42 || bfIn.bfOffBits != 54 || biIn.biSize != 40 ||
        biIn.biBitCount != 24 || biIn.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //MY CODE
    // Assign infile's BITMAPFILEHEADER to outfiles BITMAPFILEHEADER
    bfOut = bfIn;

    // Assign infile's BITMAPINFOHEADER to outfiles BITMAPINFOHEADER
    biOut = biIn;

    //what's changing: file size, image size, width, height

    //Width of resized Image(not including pixels) & Height of Image
    biOut.biWidth = biIn.biWidth * n;
    biOut.biHeight = biIn.biHeight * n;

    //determine padding for scanlines for in and out files
    int paddingIn = (4 - (biIn.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut = (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Total Size of resized Image: (includes pixles and padding)
    biOut.biSizeImage = ((sizeof(RGBTRIPLE) * biOut.biWidth) + paddingOut) * abs(biOut.biHeight);

    //Total size of resized file in bytes, includes pixles, padding & header
    bfOut.bfSize = biOut.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    //Define array to store one row of resized pixles
    RGBTRIPLE *row_pixles = malloc(biOut.biWidth * sizeof(RGBTRIPLE));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biIn.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        int count = 0;
        for (int j = 0; j < biIn.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //store each pixle n times to array, (scaling horizontally)
            for (int m = 0; m < n; m++)
            {
                //row_pixles[j * n + m] = triple;
                row_pixles[count] = triple;
                count++;
            }
        }

        //Write array to outfile n times, (scaling vertically)
        for (int m = 0; m < n; m++)
        {
            //fwrite(row_pixles, sizeof(row_pixles), 1, outptr);
            fwrite(row_pixles, sizeof(RGBTRIPLE), biOut.biWidth, outptr);

            //write outfile padding
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip over padding of infile, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }
    //Free allocated memory on heap
    free(row_pixles);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
