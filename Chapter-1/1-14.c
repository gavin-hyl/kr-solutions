/**
 * @file 1-14.c
 * @author Gavin Hua
 * @brief 1-14: Write a program to print a histogram of the frequencies of
 * different characters in its input
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    const int ALPHABET_LEN = 26;
    char c, len = 0;
    unsigned int frequency_distribution[ALPHABET_LEN];
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        frequency_distribution[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        c = tolower(c);

        if (isalpha(c))
        {
            frequency_distribution[c - 'a']++;
        }
    }

    printf("frequency distribution of word length in input text \n");
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        printf("%c | ", i + 'a');
        for (int j = 0; j < frequency_distribution[i]; j++)
        {
            putchar('=');
        }
        putchar('\n');
    }
}