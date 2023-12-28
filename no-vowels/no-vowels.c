// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string input); //Reminding the complier that the function exists

int main(int argc, string argv[])
{
    //checking if the user has provided only one command line argument
    if (argc == 2)
    {
        string replaced = replace(argv[1]);
        printf("%s\n", replaced);
    }

    else
    {
        printf("One Command-line argument is needed.\n"); //error message
        return 1; //error return value
    }
}

string replace(string input)
{
    for(int i = 0; input[i] != '\0'; i++)
    {
        switch (input[i])
        {
            case 'a':
                input[i] = '6';
                break;

            case 'e':
                input[i] = '3';
                break;

            case 'i':
                input[i] = '1';
                break;

            case 'o':
                input[i] = '0';
                break;

            default:
                break;
        }
    }
    return input;
}