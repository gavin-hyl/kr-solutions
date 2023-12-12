/**
 * @file 5-7.c
 * @author Gavin Hua
 * @brief Rewrite readlines to store lines in an array supplied by main, rather
 * than calling alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define BUFF_LEN 10000
#define MAX_LINES 100

int get_line(char *);
int read_lines(char **, int, char *, int);

char *lines[MAX_LINES]; // this stores pointers to line beginnings in buf_str

int main(void)
{
    char buf_str[BUFF_LEN];
    int buff_ind = 0;
    int n_lines = read_lines(lines, MAX_LINES, buf_str, buff_ind);
    for (int i = 0; i < n_lines; i++)
    {
        printf("Line %d: %s\n", i + 1, lines[i]);
    }
}

/**
 * @brief Read a line from user input (without \n)
 *
 * @param s the char array for which the line will be read into
 * @return the number of characters read, 0 if EOF encountered
 */
int get_line(char *s)
{
    int len = 0;
    for (; (*s = getchar()) != '\n' && (*s++ != EOF); len++)
        ;
    *s = '\0';
    return len * (*s != EOF);
}

/**
 * @brief Read all lines from input until EOF is reached
 *
 * @param lines the array of pointers to the beginnings of lines
 * @param maxLines the length of lines
 * @param buf_str the buffer string to store the lines
 * @param buff_ind the index of the next free positions of the buffer
 * @return the number of lines
 */
int read_lines(char **lines, int maxLines, char *buf_str, int buff_ind)
{
    int len = 0, n_lines = 0;
    char str[MAX_LINE];
    while ((len = get_line(str)) > 0)
    {
        if (n_lines >= maxLines || buff_ind > BUFF_LEN)
        {
            return -1;
        }
        lines[n_lines++] = buf_str + buff_ind;
        for (int i = 0; i <= len; i++)
        {
            buf_str[buff_ind++] = str[i];
        }
    }
    return n_lines;
}
