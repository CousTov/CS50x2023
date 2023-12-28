#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size -- DONE
    int initialSize;
    do
    {
        initialSize = get_int("Starting population: ");
    }
    while (initialSize < 9);

    // TODO: Prompt for end size -- DONE
    int finalSize;
    do
    {
        finalSize = get_int("End population: ");
    }
    while (finalSize < initialSize);

    // TODO: Calculate number of years until we reach threshold -- DONE
    int years = 0;
    while (initialSize < finalSize)
    {
        initialSize += initialSize / 3 - initialSize / 4;
        years++;
    }

    // TODO: Print number of years -- DONE
    printf("Years: %i\n", years);
}
