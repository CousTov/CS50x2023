#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A'); //Making sure the user does not imput any letters other than 'A' or 'T'

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function -- DONE
float calc_hours(int hours[], int weeks, char output)
{
    float sum = 0;
    float avg = 0;

    //Calculating sum as global because it will be used irrespective of what the user inputs.
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }

    if (output == 'T')
    {
        return sum;
    }

    else    // The reason else does not have a condition is because, the input will always be 'A' if it is not 'T' thanks to the do ... while loop - line: 18-22
    {
        avg = sum / weeks;
        return avg;
    }
}