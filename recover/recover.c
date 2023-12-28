#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Ensuring proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }

    char *rawFile = argv[1];

    //open the raw file
    FILE *raw = fopen(rawFile, "r");

    // If the raw file input can't be opened
    if (raw == NULL)
    {
        printf("Can not open file %s\n", rawFile);
        return 1;
    }

    //buffer to store one block
    BYTE bufferBlock[BLOCK_SIZE];

    //variable to keep count of jpegs
    int jpegCount = 0;

    //undeclared char array of size [4*8]
    char outFileName[4 * 8];

    FILE *out;

    //Look through the raw file until the end [from hints]
    while (fread(bufferBlock, 1, BLOCK_SIZE, raw) == BLOCK_SIZE)
    {
        // Check if the first 4 bytes of a block signifies the origin of a jpeg file
        if (bufferBlock[0] == 0xff && bufferBlock[1] == 0xd8 && bufferBlock[2] == 0xff && ((bufferBlock[3] & 0xf0) == 0xe0))
        {
            // Check if the count of the jpeg files is 0
            if (jpegCount == 0)
            {
                // If 0, store file name in outFileName array (outFileName, "%03i.jpeg", jpegCount)
                sprintf(outFileName, "%03i.jpg", jpegCount);

                //Create a file "out" in write mode with the name set to outFileName
                out = fopen(outFileName, "w");

                //Start writing the block consisting of BLOCK_SIZE members each of size 1
                fwrite(bufferBlock, 1, BLOCK_SIZE, out);
                //increase jpegCount by 1
                jpegCount++;
            }

            //if not 0, then close the file
            else
            {
                fclose(out);
                sprintf(outFileName, "%03i.jpg", jpegCount);
                out = fopen(outFileName, "w");
                fwrite(bufferBlock, 1, BLOCK_SIZE, out);
                jpegCount++;
            }
        }
        //if not origin of jpeg, and jpegCount > 0
        else if (jpegCount > 0)
        {
            // keep writing
            fwrite(bufferBlock, 1, BLOCK_SIZE, out);
        }
    }

    //Closing the files
    fclose(out);
    fclose(raw);

}