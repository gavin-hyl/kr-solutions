/**
 * @file 1-22.c
 * @author Gavin Hua
 * @brief 1-22: Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 512
#define FORCE_BREAK 20

int get_break(char[], int);
int get_line(char[], int);

int main()
{
    char line[MAX_LINE], split[MAX_LINE];
    char *linep = line;
    int len, break_pos;
    while ((len = get_line(line, MAX_LINE)) != EOF)
    {
        if (len < FORCE_BREAK)
        {
            printf(line);
        }
        else
        {
            while (&line[len] - linep > FORCE_BREAK)
            {
                break_pos = get_break(linep, FORCE_BREAK);
                strncpy(split, linep, break_pos);
                split[break_pos] = '\0';
                printf("%s\n", split);
                linep += break_pos;
            }
            printf(linep);
        }
    }
}

/**
 * @brief Determine where a line should be broken, going from back to front
 *
 * @param line the line
 * @param force_break the maximum length for the line to continue
 * @return the break position
 */
int get_break(char line[], int force_break)
{
    int p = force_break;
    while (p > 0)
    {
        if (isspace(line[p]))
        { // include the space so that it doesn't appear at the beginning of the next line
            return p + 1;
        }
        p--;
    }
    return force_break;
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
    int c, i = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
        s[i] = '\0';
        return i;
    }
    else
    {
        s[i] = '\0';
        return EOF;
    }
}