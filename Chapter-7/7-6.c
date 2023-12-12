/*
    Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main()
{
    FILE *f1 = fopen("7-6-1.txt", "r");
    FILE *f2 = fopen("7-6-2.txt", "r");
    int nline = 0;
    char s1[MAXLINE], s2[MAXLINE];
    while (fgets(s1, MAXLINE, f1) != NULL && fgets(s2, MAXLINE, f2) != NULL
             && strcmp(s1, s2) == 0)
    {
        nline++;
    }
    if (strcmp(s1, s2) != 0)
    {
        printf("The two files differ on line %d\n", nline);
        printf("file 1: %s\n", s1);
        printf("file 2: %s\n", s2);
    }
    else
    {
        printf("The two files have identical contents.");
    }
    fclose(f1);
    fclose(f2);
    return 0;
}