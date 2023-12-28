#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Declaring that the functions exist.
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Getting string from the user.
    string inputText = get_string("Text: ");

    //Calculating the average words and average sentences with the help of the declarad functions: count_letters(), count_sentences(), and count_words().
    float averageWords = (float)count_letters(inputText) / count_words(inputText) * 100;
    float averageSentences = (float)count_sentences(inputText) / count_words(inputText) * 100;

    //Calculating the grade level using the Coleman-Liau formula.
    int gradeLevel = round(0.0588 * averageWords - 0.296 * averageSentences - 15.8);

    //Limiting the output so it only displays grade level 1 to 16.
    if (gradeLevel >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (gradeLevel < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", gradeLevel);
    }
}

//Function to count letters
int count_letters(string text)
{
    int total = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            total++;
        }
        else if (islower(text[i]))
        {
            total++;
        }
    }
    return total;
}

//Function to count words
int count_words(string text)
{
    int total = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            total++;
        }
    }
    return total;
}

//Function to count sentences
int count_sentences(string text)
{
    int total = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            total++;
        }
    }
    return total;
}