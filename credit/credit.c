#include <cs50.h>
#include <stdio.h>

long getCardNumber(void);
string checkCard(long number);

int main(void)
{
    long cardNumber = getCardNumber();
    checkCard(cardNumber);
}

long getCardNumber(void)
{
    //Prompt the user to input card number
    return 0;
}

string checkCard(long number)
{
    //Check if the 1st (and 2nd) digit(s) corresponds to that of a standard VISA card, or MasterCard, or AmericanExpress. If it does not, print INVALID.
    return 0;
}