#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Reminding the complier that the functions exists
    int getHeight(void);
    void printPyramid(int);

    //Getting the height of the pyramid
    int height = getHeight();

    //Printing the pyramid
    printPyramid(height);

}

//function for getting height
int getHeight(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

//function for printing pyramid
void printPyramid(int height)
{
    //main loop that iterates until i equals height given
    for (int i = 0; i < height; i++)
    {
        //loop for printing height - 1 number of blank spaces
        for (int k = height - 1; k > i; k--)
        {
            printf(" ");
        }

        //loop for printing n hashes per nth iteration after the previous loop puts height - 1 number of blank spaces
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n"); //new line each time the two previous loops conclude
    }
}