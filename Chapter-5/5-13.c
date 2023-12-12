/**
 * @file 5-13.c
 * @author Gavin Hua
 * @brief 5-13: Write the program tail, which prints the last n lines of its input.
 * By default, n is set to 10, let us say, but it can be changed by an optional
 * argument so that "tail -n" prints the last n lines. The program should behave
 * rationally no matter how unreasonable the input or the value of n. Write the
 * program so it makes the best use of available storage; lines should be stored
 * as in the sorting program of Section 5.6, not in a two-dimensional array of
 * fixed size.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 10000
#define MAXLEN 100

int readlines(char *[], int);
int get_line(char *, int);

char *lines[MAXLINES];

int main(int argc, char *argv[])
{
    printf((argc == 1) ? "Usage: print last n lines of input.\n" : "");

    int n = (argc == 2) ? atof(*++argv + 1) : 10;
    if (!n)
    {
        printf("argument invalid, returning to default setting (n=10).\n");
    }

    int nlines = readlines(lines, MAXLINES);

    for (int i = 0; (i <= n) && (i <= nlines); i++)
    {
        printf("%s\n", lines[nlines - i]);
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
int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    else if (c == EOF)
    {
        return -1;
    }
    s[i] = '\0';
    return i;
}

/**
 * @brief Read input lines into an array of strings
 * 
 * @param lines the array
 * @param lim the length of lines
 * @return the lines read
 */
int readlines(char *lines[], int lim)
{
    int len, n_lines;
    char *p, line[MAXLEN];
    n_lines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (n_lines >= lim || (p = malloc(len * sizeof(char))) == NULL)
        {
            printf("Error.\n");
            return -1;
        }
        else
        {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lines[n_lines++] = p;
        }
    }

    return n_lines;
}