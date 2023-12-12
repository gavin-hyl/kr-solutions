/**
 * @file 5-15.c
 * @author Gavin Hua
 * @brief Exercise 5-15.
 *
 * Add the option -f to fold upper and lower case together, so that case
 * distinctions are not made during sorting; for example, a and A compare equal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 10000
#define MAXLEN 100

void my_qsort(void *[], int (*comp)(void *, void *), int, int);
int numcmp(char *, char *);
int my_strcmp(char *, char *);
void swap(void *[], int, int);
int readlines(char *[], int);
void writelines(char *[], int);
void trim_dir(char *);

char *lines[MAXLINES];
int n_lines, reverse, fold, dir, num;

int main(int argc, char *argv[])
{
    argv++;
    while (*argv != NULL)
    {
        reverse += ((*argv)[1] == 'r');
        fold += ((*argv)[1] == 'f');
        num += ((*argv)[1] == 'n');
        argv++;
    }

    reverse = reverse ? -1 : 1;

    n_lines = readlines(lines, MAXLINES);
    my_qsort((void **)lines, (int (*)(void *, void *))(num ? numcmp : my_strcmp), 0, n_lines - 1);
    writelines(lines, n_lines);

    return 0;
}

/**
 * @brief Quicksort implementation
 *
 * @param v the array to be sorted
 * @param comp the comparison function
 * @param left the left index of the sub-array to sort
 * @param right the right index of the sub-array to sort
 */
void my_qsort(void *v[], int (*comp)(void *, void *), int left, int right)
{
    int i, last;

    if (left >= right)
    {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (reverse * (*comp)(v[i], v[left]))
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    my_qsort(v, comp, left, last - 1);
    my_qsort(v, comp, last + 1, right);
}

/**
 * @brief Compare two strings by comparing their corresponding float values
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return 1 if s1<s2, 0 otherwise
 */
int numcmp(char *s1, char *s2)
{
    return (atof(s1) < atof(s2));
}

/**
 * @brief Compare two strings lexicographically. If fold, then ignore case.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return if s1<s2, 0 otherwise
 */
int my_strcmp(char *s1, char *s2)
{
    char *s1cpy = malloc(sizeof(char) * strlen(s1));
    char *s2cpy = malloc(sizeof(char) * strlen(s2));
    strcpy(s1cpy, s1);
    strcpy(s2cpy, s2);
    if (fold)
    {
        s1cpy = strlwr(s1cpy);
        s2cpy = strlwr(s2cpy);
    }
    return strcmp(s1cpy, s2cpy) < 0;
}

/**
 * @brief Swap two elements in an array
 *
 * @param v the array
 * @param a the index of the first element
 * @param b the index of the second element
 */
void swap(void *v[], int a, int b)
{
    void *temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
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
int readlines(char *lineptr[], int maxlines)
{
    int len, n_lines;
    char *p, line[MAXLEN];
    n_lines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (n_lines >= maxlines || (p = malloc(len * sizeof(char))) == NULL)
        {
            printf("Error.\n");
            return -1;
        }
        else
        {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[n_lines++] = p;
        }
    }

    return n_lines;
}

/**
 * @brief Print all strings in an array of strings
 *
 * @param lines the array
 * @param n the number of strings in lines
 */
void writelines(char *lineptr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}