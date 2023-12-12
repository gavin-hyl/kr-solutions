/**
 * @file 2-4.c
 * @author Gavin Hua
 * @brief Write an alternative version of squeeze(s1,s2) that deletes each
 * character in s1 that matches any character in the string s2.
 */

#include <stdio.h>

void squeeze(char[], char[]);

int main()
{
    char s1[] = "a1b1c2d2e1f2g";
    char s2[] = "12";
    squeeze(s1, s2);
    printf("%s", s1);
    return 0;
}

/**
 * @brief Deletes each character in s1 that matches any 
 * character in the string s2.
 * 
 * @param s1 the string to be squeezed
 * @param s2 the squeeze characters
 */
void squeeze(char s1[], char s2[])
{
    int i = 0, j = 0;
    for (; s1[i] != '\0'; i++)
    {
        for (int k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
                i++;
        }
        s1[j++] = s1[i];
    }
    s1[j] = '\0';
}