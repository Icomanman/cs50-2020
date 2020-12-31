#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int k;

int main(int argc, string argv[])
{

	if (argc != 2)
	{
		printf("error\n");
		return 1;
	}

	k = atoi(argv[1]);

	/*
	if (k < 0)
	{W
		printf("please enter a positive integer\n");
		return 1;
	}
	*/
	string p = get_string("plaintext: ");

	int n = strlen(p);

	//cipher key...
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

	/*int mod = (75 - 64) % 26 + 64;
	/char cmod = char(mod);
	printf("%c and %c \n", mod, mod);*/
}