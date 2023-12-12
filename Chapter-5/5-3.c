/**
 * @file 5-3.c
 * @author Gavin Hua
 * @brief 5-3: Write a pointer version of the function strcat that we showed in
 * Chapter 2: strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

void str_cat(char *, char *);

int main(void)
{
    char s[100] = "hello ";
    char t[] = "world!";
    str_cat(s, t);
    printf(s);
    return 0;
}

/**
 * @brief Copies the string t to the end of s. Note that this is dangerous if s
 * is not initialized to be long enough to hold s and t.
 *
 * @param s the base string
 * @param t the stirng to be copied
 */
void str_cat(char *s, char *t)
{
    while (*(++s))
        ;
    while (*s++ = *t++)
        ;
}