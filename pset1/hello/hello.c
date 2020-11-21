#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); // prompts the user for his or her name
    printf("Hello, %s!\n", name); // prints the user's name
}