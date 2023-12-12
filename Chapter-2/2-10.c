/**
 * @file 2-10.c
 * @author Gavin Hua
 * @brief Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
 */

#include <stdio.h>

void lower(char[]);

int main(int argc, char const *argv[])
{
    char s[] = "AaBb123";
    lower(s);
    printf("%s", s);
    return 0;
}

/**
 * @brief Converts uppercase letters in a string to lower case
 *
 * @param s the string
 */
void lower(char s[])
{
    for (int i = 0; s[i]; i++)
    {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? (s[i] - 'A' + 'a') : s[i];
    }
}