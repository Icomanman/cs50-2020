#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
Coleman-Liau index Formula
index = 0.0588 * L - 0.296 * S - 15.8
L 	= avg. letters per 100 words
	= letters * 100 / words
S 	= avg. sentences per 100 words
	= sentences * 100 / words
space = int(32), end of a word
['.', '!', '?'] = end of a sentence, int[46, 33, 63]
*/

// Uppercase: 65 to 90
// Lowercase: 97 to 122

// part of math.h
double pow10(double x);
double round(double x);

int main(void)
{
	const int BASE = 10;
	double letters = 0;
	double words = 0;
	double sentences = 0;
	double index = 0;
	double L, S;
	int grade = 0;
	char last_char = 46; // initialised as a period '.'

	string s = get_string("Text: ");
	unsigned long txt_len = strlen(s);

	// repeatedly prompt the user for proper words:
	while (txt_len < 2)
	{
		s = get_string("Text: ");
		txt_len = strlen(s);
	}
	words = 1;
	last_char = s[txt_len - 1];

	// count the sentences and words based on the contents
	for (int i = 0; i < txt_len; i++)
	{
		int ascii = (int)s[i];
		if (ascii == 32)
		{
			words++;
		}
		else if (ascii == 33 || ascii == 46 || ascii == 63)
		{
			sentences++;
		}
		else if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
		{
			letters++;
		}
	}

	/*
	when no period, question mark or exclamation point at the end of the text,
	assume a single sentence
	*/

	if (last_char != 46 && last_char != 33 && last_char != 63 && last_char != 34)
	{
		sentences++;
	}

	L = letters * 100. / words;
	S = sentences * 100. / words;
	index = 0.0588 * L - 0.296 * S - 15.8;
	index = round(index);
	/*
	printf("letters: %f\n", letters);
	printf("words: %f\n", words);
	printf("sentences: %f\n", sentences);
	printf("L, S and index: %f, %f and %.3f\n", L, S, index);
	*/
	if (index < 1)
	{
		printf("Before Grade 1...\n");
	}
	else if (index > 16)
	{
		printf("Grade 16+\n");
	}
	else
	{
		printf("Grade %.0f\n", index);
	}
}

// Calculate Exponents
long long raiseTo(int exp)
{
	const int BASE = 10;
	long long result = 1;

	while (exp > 0)
	{
		result *= BASE;
		exp--;
	}
	return result;
}