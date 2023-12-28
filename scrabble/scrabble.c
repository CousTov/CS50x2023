#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner - Done
    if (score1 < score2)
    {
        printf("Player 2 wins\n");
    }
    else if (score2 < score1)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{

    // TODO: Compute and return score for string - Done
    int totalScore = 0;

    //Checking if we have reached the end of the string. Imput string, which is an array of chars, will always have '\0' as it's last indexable value.
    //Taken from my solution of practice problems.
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isupper(word[i]))
        {
            totalScore += POINTS[word[i] - 'A']; //Letters are just numbers as long as the computer is concerned.
        }
        else if (islower(word[i]))
        {
            totalScore += POINTS[word[i] - 'a']; //Letters are just numbers as long as the computer is concerned.
        }
    }

    return totalScore;
}