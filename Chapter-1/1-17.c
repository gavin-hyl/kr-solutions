/**
 * @file 1-17.c
 * @author Gavin Hua
 * @brief 1-17: Write a program to print all input lines that are longer 
 * than 80 characters.
 */

#include <stdio.h>

int get_line(char[], int);

int main()  
{
    const int MAXLENGTH = 300, THRESH_LENGTH = 80;
    int len = 0;
    char line[MAXLENGTH];

    while ((len = get_line(line, MAXLENGTH)) != EOF)
    {
        if (len > THRESH_LENGTH)
        {
            printf("%s", line);
        }
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
