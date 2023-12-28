#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Enter your name: "); //Assigns the value returned by get_string function into the variable name.
    printf("hello, %s\n", name); //Prints as "hello, name", after %s, a string placeholder, gets replaced with name.
}