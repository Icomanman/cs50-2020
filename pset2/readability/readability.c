#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Coleman-Liau index Formula
// index = 0.0588 * L - 0.296 * S - 15.8

int main()
{
    string s = get_string("Please enter: ");
    int i = 0, j = 0;

    //first string - make sure it's not a 'space'
    while (i < strlen(s))
    {
       if (s[i] == ' ')
       {
           i++;
       }
       else
        {
            if (s[i] > 96 && s[i] < 123)
            {
            printf("%c", toupper(s[i]));
            }
            else
            {
            printf("%c", s[i]);
            }
            break;
        }
    }

    j = i+1;


    //succeeding strings - search for the next 'space'
    for (j = i+1; j < strlen(s) - 1; j++)
    {
       while (s[j] != 32)
       {
           j++;

           if (s[j] == '\0')
            {
                printf("\n");
                exit(0);
            }
       }
        while (s[j] == 32)
        {
            j++;
            if (s[j] == '\0')
            {
                printf("\n");
                exit(0);
            }
        }
        if (s[j] > 96 && s[j] < 123 && s[j] != '\0')
        {
            printf("%c", toupper(s[j]));

        }
        else
        {
        printf("%c", s[j]);
        }
    }
    //printf("\n%lu", strlen(s));
}
