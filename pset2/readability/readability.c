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

int main(void)
{
	string s = get_string("Text: ");
	unsigned long txt_len = strlen(s);
	while (txt_len < 2)
	{
		s = get_string("Text: ");
		txt_len = strlen(s);
	}
	printf("The length is: %lu\n", txt_len);

	int words = 0;
	int sentences = 0;
	for (int i = 0; i < txt_len; i++)
	{
		int ascii = (int)s[i];
		if (ascii == 32)
		{
			words++;
		};
		if (ascii == 33 || ascii == 46 || ascii == 63)
		{
			sentences++;
		}
	}
	printf("words: %i\n", words);
	printf("sentences: %i\n", sentences);
}
