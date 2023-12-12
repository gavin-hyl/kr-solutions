/**
 * @file 1-18.c
 * @author Gavin Hua
 * @brief 1-18: Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_trailing_whitespace(char[]);
int get_line(char[], int);

int main()  
{
    const int MAXLENGTH = 300, THRESH_LENGTH = 80;
    int len = 0;
    char line[MAXLENGTH];

    while ((len = get_line(line, MAXLENGTH)) != EOF)
    {
        trim_trailing_whitespace(line);
        printf("%s", line);
    }
}

/**
 * @brief Read a line from user input
 *
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the number of read characters
 */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/**
 * @brief Trim the trailing whitespace in a string
 * 
 * @param s the string to be trimmed
 */
void trim_trailing_whitespace(char s[])
{
    unsigned int len = strlen(s);
    if (len == 0 || s[1] == '\n')
    {
        s[0] = '\0';
        return;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        if (!isblank(s[i]))
        {
            s[i+1] = '\0';
            return;
        }
    }
}