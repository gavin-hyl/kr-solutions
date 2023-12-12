/**
 * @file 4-12.c
 * @author Gavin Hua
 * @brief 4-12: Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 */

#include <stdio.h>

void recursive_itoa(const int, char[]);

int main(void)
{
    char s[100];
    recursive_itoa(1230245, s);
    printf(s);
    return 0;
}

/**
 * @brief Converts an integer into a string recursively
 * 
 * @param i the integer
 * @param to its string representation
 */
void recursive_itoa(const int i, char to[])
{
    static int current_length;
    if (i == 0)
    {
        to[current_length] = '\0';
    }
    else
    {
        for (int a = current_length; a >= 0; a--)
        {
            to[a + 1] = to[a];
        }
        current_length++;
        to[0] = i % 10 + '0';
        recursive_itoa(i / 10, to);
    }
}
