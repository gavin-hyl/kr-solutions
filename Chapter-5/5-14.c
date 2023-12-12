/*
    Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.
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
void formatdir(char *);

char *lines[MAXLINES];
int nlines, reverse, fold, dir, num;

int main(int argc, char *argv[])
{
    argv++;
    while (*argv != NULL)
    {   // assuming each option appears only once, no error checking
        reverse += ((*argv)[1] == 'r');
        num += ((*argv)[1] == 'n');
        argv++;
    }

    reverse = reverse ? -1 : 1;

    nlines = readlines(lines, MAXLINES);
    my_qsort((void **)lines, (int (*)(void *, void *)) (num ? numcmp : my_strcmp), 0, nlines-1);
    writelines(lines, nlines);

    return 0;
}

void my_qsort(void *v[], int (*comp)(void *, void *), int left, int right)
{
    int i, last;
    
    if (left >= right)
    {
        return;
    }
    swap(v, left, (left+right)/2);
    last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (reverse * (*comp)(v[i], v[left]))
        {
            swap(v, ++last, i); 
        }
    }
    swap(v, left, last);
    my_qsort(v, comp, left, last-1);
    my_qsort(v, comp, last+1, right);
}


int numcmp(char *s1, char *s2)
{
    return (atof(s1) < atof(s2));
}

int my_strcmp(char *s1, char *s2)
{   
    return strcmp(s1, s2) < 0;
}

void swap(void *v[], int a, int b)
{
    void *temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c!='\n'; i++)
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

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = malloc(len * sizeof(char))) == NULL)
        {
            printf("Error.\n");
            return -1;
        }
        else 
        {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}