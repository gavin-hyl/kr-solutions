/**
 * @file 1-6.c
 * @author Gavin Hua
 * @brief 1-6: Verify that the expression getchar() != EOF is 0 or 1
 */

#include <stdio.h>

int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        printf("%d ", (c != EOF));
    }
    printf("%d", (c != EOF));
}