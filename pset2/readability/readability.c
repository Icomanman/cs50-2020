#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

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

int main(void)
{

	unsigned long letters = 0;
	unsigned long words = 0;
	int sentences = 0;
	double index = 0;
	double L, S;

	string s = get_string("Text: ");
	unsigned long txt_len = strlen(s);

	// repeatedly prompt the user for proper words:
	while (txt_len < 2)
	{
		s = get_string("Text: ");
		txt_len = strlen(s);
	}
	words = 1;

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

	L = letters * 100 / words;
	S = sentences * 100 / words;
	index = (0.0588 * L) - (0.296 * S) - 15.8;
	/*
	printf("letters: %lu\n", letters);
	printf("words: %lu\n", words);
	printf("sentences: %i\n", sentences);
	printf("L, S and index: %f, %f and %.3f\n", L, S, index);
	*/
}