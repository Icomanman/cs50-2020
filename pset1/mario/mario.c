#include <stdio.h>
#include <cs50.h>

void space(int n);
void sharp(int n);
void sharpl(void);

int main(void)
{
    int h;
    int i = 1;

    do
    {
        // prompts the user for an input and assigns it to 'h'
        h = get_int("Height: ");
    }
    while (h <= 0 || h > 8); // input can be between 0 and 8

    int j = h - i;

    while (i <= h)
    {
        space(j);
        sharp(i);
        space(2);
        sharp(i);
        sharpl();
        i++;
        j--;
    }
}

// Function that writes the spaces
void space(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%c", ' ');
    }
}

// Function that writes the hashes
void sharp(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%c", '#');
    }
}

// Function that writes a new line
void sharpl(void)
{
    printf("\n");
}
