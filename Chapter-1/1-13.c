/**
 * @file 1-13.c
 * @author Gavin Hua
 * @brief 1-13: Write a program to print a histogram of the lengths 
 * of words in its input.
 */

#include <stdio.h>

int main()
{
    const int MAX_LEN = 14;
    char c, len = 0;
    unsigned int frequency_distribution[MAX_LEN];
    for (int i = 0; i < MAX_LEN; i++)
    {
        frequency_distribution[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c != '\n' && c != ' ' && c != '\t')
        {
            len++;
        }
        else
        {
            frequency_distribution[len]++;
            len = 0;
        }
    }

    printf("frequency distribution of word length in input text 、\n");
    for (int i = 1; i <= MAX_LEN; i++)
    {
        printf("%2d | ", i);
        for (int j = 0; j < frequency_distribution[i-1]; j++)
        {
            putchar('=');
        }
        putchar('\n');
    }
}