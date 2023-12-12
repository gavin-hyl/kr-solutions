/**
 * @file 2-2.c
 * @author Gavin Hua
 * @brief 2-2: Write a loop equivalent to the for loop above without
 * using && or ||
 * 
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * {
 *      s[i] = c;
 * }
 */

#include <stdio.h>

int main()
{
    const int lim = 10;
    char s[lim];
    int c;
    for (int i = 0;; ++i)
    {
        s[i] = c;
        if (i > lim - 1)
        {
            break;
        }
        c = getchar();
        if (c == '\n')
        {
            break;
        }
        if (c == EOF)
        {
            break;
        }
    }
}