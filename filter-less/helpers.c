#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Cycle through each row of pixels in an image
    for (int i = 0; i < height; i++)
    {
        //Cycle through each column of pixels in an image
        for (int j = 0; j < width; j++)
        {
            // Finding average from original 3 color values
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // Applying the average to all three colors to give appriopriate shade of black
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // temp pixel varable to store pixel data (RGB values) before calculations
    RGBTRIPLE pixel;

    // Variables to store sepia values of each RGB color
    int sepiaRed, sepiaBlue, sepiaGreen;

    // Looping through each row of pixels in image
    for (int i = 0; i < height; i++)
    {
        // Looping through each column of pixels in image
        for (int j = 0; j < width; j++)
        {
            // Storing the RGB values of original pixel at image[i][j] to temp variable pixel
            pixel.rgbtRed = image[i][j].rgbtRed;
            pixel.rgbtGreen = image[i][j].rgbtGreen;
            pixel.rgbtBlue = image[i][j].rgbtBlue;

            // Applying given algorithm to get the sepia equavalent of each color value from pixel
            sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

            // Correcting if the value from algorithm exceeds maximum 225
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Applying sepia to pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temp pixel to store pixel data (RGB values)
    RGBTRIPLE pixel;

    // Looping through each row of pixels in image
    for (int i = 0; i < height; i++)
    {
        // Looping through each columns of pixels in image untill half of image is reached (width / 2)
        for (int j = 0; j < width / 2; j++)
        {
            // Storing original pixel data in temp pixel variable
            pixel = image[i][j];

            // Exchanging pixel data (or for easier intrepretion, exchanging pixel positions)
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = pixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temp 2D copy variable to copy original image
    RGBTRIPLE copy[height][width];

    // For loop copy image to copy, pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For loop to cycle through each row of temp (i < height)
    for (int i = 0; i < height; i++)
    {
        // For loop to cycle through each column of temp (j < width)
        for (int j = 0; j < width; j++)
        {
            // variables to store total red, green, and blue values of true pixels. Extra variable pixelCount to store "true pixel" count
            int red = 0, green = 0, blue = 0, pixelCount = 0;

            // variables to store averages of total RGB values seperately
            int averageRed, averageBlue, averageGreen;

            // For loop to move 1 x-unit from 0,0 (-1 <= x <= 1)
            for (int axisX = -1; axisX < 2; axisX++)
            {
                // For loop to move 1 y-unit from x,0 (-1 <= y <= 1)
                for (int axisY = -1; axisY < 2; axisY++)
                {
                    // Noting the X and Y position after moving
                    int currX = i + axisX;
                    int currY = j + axisY;

                    // If the "pixle position" after moving 1 x-unit and 1 y-unit is within the height and width of the image
                    if (currX >= 0 && currX < height && currY >= 0 && currY < width)
                    {

                        // add the red, green and blue values of pixel to respective variables
                        red += copy[currX][currY].rgbtRed;
                        green += copy[currX][currY].rgbtGreen;
                        blue += copy[currX][currY].rgbtBlue;

                        // increment count of "true pixels"
                        pixelCount++;
                    }
                }
            }

            // Calculate average red, green, blue by dividing the respective totals with true pixel count
            averageRed = round(1.00 * red / pixelCount);
            averageGreen = round(1.00 * green / pixelCount);
            averageBlue = round(1.00 * blue / pixelCount);

            // apply to image[i][j] pixel by pixel
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
}