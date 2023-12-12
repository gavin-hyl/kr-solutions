/**
 * @file 1-19.c
 * @author Gavin Hua
 * @brief 1-19: Write a function reverse(s) that reverses the character 
 * string s. Use it to write a program that reverses its input a line at a time.
 */

#include <stdio.h>
#include <string.h>

int get_line(char[], int);
void reverse(char[]);

int main()
{
    const int MAXLENGTH = 300;
    char line[MAXLENGTH], c;
    int line_len = 0;
    while ((line_len = get_line(line, MAXLENGTH)) != 0)
    {
        line[line_len - 1] = '\0';
        reverse(line);
        printf("%s\n", line);
    }
    return 0;
}

/**
 * @brief Read a line from user input
 * 
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the number of characters read
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
 * @brief Reverses a string in place
 * 
 * @param s the string to be reversed
 */
void reverse(char s[])
{
    int len = strlen(s);
    char c;
    for (int i = 0; i <= (len / 2); i++)
    {
        c = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = c;
    }
}