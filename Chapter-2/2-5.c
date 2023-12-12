/**
 * @file 2-5.c
 * @author Gavin Hua
 * @brief 2-5: Write the function any(s1,s2), which returns the first location
 * in a string s1 where any character from the string s2 occurs. or -1 if s1
 * contains no characters from s2.
 */

#include <stdio.h>

int any(const char[], const char[]);

int main()
{
    char s1[] = "a1b1c2d2e1f2g";
    char s2[] = "12";
    int index = any(s1, s2);
    printf("%d", index);
    return 0;
}

/**
 * @brief Searches a string for characters from another
 * 
 * @param s1 the stirng to be searched
 * @param s2 the characters to look for
 * @return the first location in a string s1 where any character from the 
 * string s2 occurs. or -1 if s1 contains no characters from s2.
 */
int any(const char s1[], const char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        for (int j = 0; s2[j] != '\0'; i++)
        {
            if (s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}