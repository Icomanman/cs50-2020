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

    // Print the winner:
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

/* Char positions from POINTS[] array should correspond to ascii:
A = 65, Z = 90; a = 97, z = 122 */
int compute_score(string word)
{
    // Compute and return score for string
    int lim = sizeof(POINTS) / sizeof(int);
    int score = 0;
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        if (islower(word[i]) != 0)
        {
            // lowercase
            int pos = word[i] - 97;
            if (pos <= lim)
            {
                score = score + POINTS[pos];
            }
        } 
        else
        {
            // uppercase
            int pos = word[i] - 65;
            if (pos <= lim)
            {
                score = score + POINTS[pos];
            }
        }
    }
    return score;
}