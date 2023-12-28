#include "helpers.h"
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // An image is just a 2 dimentional grid of pixels.
    // Loop to cycle through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If pixel is black, change color (RGB VALUE IN HEX -- 0x00)
            if (image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00)
            {
                image[i][j].rgbtRed = 0x00;
                image[i][j].rgbtGreen = 0x9f;
                image[i][j].rgbtBlue = 0x00;
            }
        }
    }
}
