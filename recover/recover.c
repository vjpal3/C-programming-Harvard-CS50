#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //Open input file for reading
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    //count is used to get the number of bytes read from fread
    int count = 1;

    //buffer stores the
    uint8_t buffer[512];

    //create jpeg files within loop
    int jpegCount = 0;

    //Format the filename and Store in the string
    char jpegFilename[8];

    FILE *img = NULL;

    //if count = 0, then EOF reached, because the last fread could read less than 512 bytes and returned 0.
    while (count != 0)
    {
        //read 512 bytes in the quantity of 1
        count = fread(buffer, 512, 1, inptr);

        //Check for start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8  && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check if the a jpeg file is already open and the jpeg header of next file is found.
            //So close the already opened file.
            if (img != NULL)
            {
                fclose(img);
            }

            //Create filename for jpeg in the format '000.jpg'
            sprintf(jpegFilename, "%03i.jpg", jpegCount);
            jpegCount++;

            //Open new jpeg file for writing
            img = fopen(jpegFilename, "w");

            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s\n", jpegFilename);
            }
        }
        //Write jpeg data to the jpeg file
        //The condition checks that the EOF data (< 512 bytes) is not written to the last jpeg
        if (img != NULL && count)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    //close the last opened jpeg file
    if (img != NULL)
    {
        fclose(img);
    }

    //close the input file
    fclose(inptr);
    return 0;
}
