#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

<<<<<<< HEAD
int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("error\n");
		return 1;
	}

	int k = atoi(argv[1]);
	if (k < 48)
	{
		printf("Usage: ./caesar key\n");
		return 1;
	}
	else if (k > 57)
	{
		printf("Usage: ./caesar key\n");
		return 1;
	}
	string p = get_string("plaintext: ");

	int n = strlen(p);
	/*
	cipher key = k
	plaintext will be shifted accordingly (using the ascii code)
	*/
	int cipherKey[n];
	printf("ciphertext: ");
	for (int i = 0; i <= n - 1; i++)
	{
		if (p[i] <= 90 && p[i] >= 65)
		{
			if (((p[i] + k) - 64) % 26 == 0)
			{
				cipherKey[i] = (((p[i] + k) - 64) % 26) + 65;
			}
			else
			{
				cipherKey[i] = (((p[i] + k) - 64) % 26) + 64;
			}
		}
		else if (p[i] <= 122 && p[i] >= 65)
		{
			if (((p[i] + k) - 96) % 26 == 0)
			{
				cipherKey[i] = (((p[i] + k) - 96) % 26) + 97;
			}
			else
			{
				cipherKey[i] = (((p[i] + k) - 96) % 26) + 96;
			}
		}
		else
		{
			cipherKey[i] = p[i];
		}
		printf("%c", cipherKey[i]);
	}
	printf("\n");
=======
// updated 28 Jun 2021
// initialise k as an int
int k;

int main(int argc, string argv[])
{

    // needs exactly 1 arg besides the program name; otherwise throw an error
    if (argc != 2)
    {
        printf("error\n");
        return 1;
    }

    // converts the arg (key) into an integer
    k = atoi(argv[1]);

    // sets the range of allowable ascii char
    if (k < 0)
    {
        printf("please enter a positive integer\n");
        return 1;
    }

    // prompt for plaintext
    string p = get_string("plaintext: ");

    int n = strlen(p);
>>>>>>> 53fa4306a0530c65c71dbb0bd80459faac121bae

    // cipher key...
    int cipherKey[n];
    printf("ciphertext: ");

    for (int i = 0; i <= n - 1; i++)
    {
        // Capital Letters
        if (p[i] <= 90 && p[i] >= 65)
        {
            if (((p[i] + k) - 64) % 26 == 0)
            {
                cipherKey[i] = (((p[i] + k) - 64) % 26) + 65;
            }
            else
            {
                cipherKey[i] = (((p[i] + k) - 64) % 26) + 64;
            }
        }
        else if (p[i] <= 122 && p[i] >= 65)
        {
            if (((p[i] + k) - 96) % 26 == 0)
            {
                cipherKey[i] = (((p[i] + k) - 96) % 26) + 97;
            }
            else
            {
                cipherKey[i] = (((p[i] + k) - 96) % 26) + 96;
            }
        }
        else
        {
            cipherKey[i] = p[i];
        }
        printf("%c", cipherKey[i]);
    }
    printf("\n");
}