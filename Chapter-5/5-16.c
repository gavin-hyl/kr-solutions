/*
    Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with -f.
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
        fold += ((*argv)[1] == 'f');
        num += ((*argv)[1] == 'n');
        dir += ((*argv)[1] == 'd');
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
    char *s1cpy = malloc(sizeof(char) * strlen(s1));
    char *s2cpy = malloc(sizeof(char) * strlen(s2));
    strcpy(s1cpy, s1);
    strcpy(s2cpy, s2);
    if (fold)
    {
        s1cpy = strlwr(s1cpy);
        s2cpy = strlwr(s2cpy);
    }  
    if (dir)
    {
        formatdir(s1cpy);
        formatdir(s2cpy);
    }
    return strcmp(s1cpy, s2cpy) < 0;
}

void swap(void *v[], int a, int b)
{
    void *temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void formatdir(char *s)
{
    int i = 0, j = 0;
    while (s[i])
    {
        if (!isalnum(s[i]) && !isspace(s[i]))
        {
            i++;
        }
        else
        {
            s[j++] = s[i++];
        }
    }
    s[j] = '\0';
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