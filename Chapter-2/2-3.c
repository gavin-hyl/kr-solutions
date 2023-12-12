/**
 * @file 2-3.c
 * @author Gavin Hua
 * @brief 2-3: Write a function htoi(s), which converts a string of hexadecimal
 * digits (including an optional 0x or 0X) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f, and A through F.
 */

#include <stdio.h>

void lower(char[]);
int h_to_i(char[]);

int main()
{
    char s[] = "1a";
    printf("%d", h_to_i(s));
    return 0;
}

/**
 * @brief Convert a string from uppercase to lower
 *
 * @param s the string
 */
void lower(char s[])
{
    for (int i = 0; s[i]; i++)
    {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') * (s[i] - 'A' + 'a') +
               (s[i] < 'A' || s[i] > 'Z') * s[i];
    }
}

/**
 * @brief Converts a string of hexadecimal digits into
 * its equivalent integer value
 *
 * @param s the string
 * @return the equivalent integer value
 */
int h_to_i(char s[])
{
    int val = 0;
    int i = 0;
    lower(s);
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        i = 2;
    }
    for (; s[i]; i++)
    {
        val = 16 * val + (s[i] - '0') * (s[i] >= '0' && s[i] <= '9') +
              (s[i] - 'a' + 10) * (s[i] >= 'a' && s[i] <= 'f');
    }
    return val;
}