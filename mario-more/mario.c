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

//function for getting height (**borrowed from my mario-less code**)
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

//function for printing two pyramid from top down at once (**mostly borrowed from my mario-less code**)
void printPyramid(int height)
{
    //main loop that iterates until i equals height given
    for (int i = 0; i < height; i++)
    {
        //loop to print left pyramid blank spaces for iteration nth
        for (int k = height - 1; k > i; k--)
        {
            printf(" ");
        }

        //loop to print left pyramid hash for iteration nth
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("  "); //two blank spaces instead of new line to continue printing the next pyramid

        //loop to print the right pyramid hashes for iteration nth
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}