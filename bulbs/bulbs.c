#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    //Getting string from the user
    string inputTxt = get_string("Message: ");

    //Loop to cycle throung each char of string
    for (int i = 0, len = strlen(inputTxt); i < len; i++)
    {
        //Storing decimal value of each char before conversion occurs
        int val = inputTxt[i];

        //Making an array to store the 1s and 0s after conversion
        int dec2bin[BITS_IN_BYTE];

        //Loop to convert decimal values into binary and store them in the dec2bin[] array
        for (int j = 0; j < BITS_IN_BYTE ; j++)
        {
            dec2bin[(BITS_IN_BYTE - 1) - j] = val % 2;
            val = val / 2;
        }

        //Printing Light bulbs
        for (int j = 0; j < BITS_IN_BYTE ; j++)
        {
            print_bulb(dec2bin[j]);
        }

        //Line break after printing out bulbs
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
