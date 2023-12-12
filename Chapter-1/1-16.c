/**
 * @file 1-16.c
 * @author Gavin Hua
 * @brief 1-16: Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrary long input lines, and as much as
 * possible of the text。
 */

#include <stdio.h>
#include <string.h>

int get_line_and_len(char[], int);

int main()
{
    const int MAXLENGTH = 300;
    int len, max = 0;
    char line[MAXLENGTH], longest[MAXLENGTH];

    while ((len = get_line_and_len(line, MAXLENGTH)) != EOF)
    {
        if (len > max)
        {
            max = len;
            strcpy(longest, line);
        }
    }
    if (max > 0)
    {
        printf("Longest line is \n%s", longest);
        printf("It has length %d", max);
    }
    return 0;
}

/**
 * @brief Read a line from user input
 * 
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the length of the line (may be greater than lim)
 */
int get_line_and_len(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    switch (c)
    {
    case ('\n'):
        s[i] = c;
        s[i + 1] = '\0';
        return i + 1;
    case (EOF):
        return EOF;
    default:
        s[lim - 1] = '\0';
        for (; (c = getchar()) != EOF && c != '\n'; i++)
            ;
        return lim;
    }
}
