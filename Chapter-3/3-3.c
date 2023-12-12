/**
 * @file 3-3.c
 * @author Gavin Hua
 * @brief 3-3: Write a function expand(s1,s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc...xyz in s2. 
 * Allow for letters of either case and digits, and be prepared to handle cases 
 * like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is 
 * taken literally. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void expand(const char [], char [], int);

int main()
{
    const int MAX_STR = 1000;
    char s1[MAX_STR], s2[MAX_STR];
    fgets(s1, MAX_STR, stdin);
    expand(s1, s2, MAX_STR);
    printf(s2);
    return 0;
}

/**
 * @brief Expands shorthand notations such as a-z into abc...xyz
 * 
 * @param s1 the string to be expanded
 * @param s2 the expanded string
 * @param max_s2 maximum length of the expanded string
 */
void expand(const char s1[], char s2[], int max_s2)
{
    int s2_ind=0;
    char current;
    int len = strlen(s1);

    for(int i = 0; i < len; i++)
    {
        s2[s2_ind++] = current = s1[i];

        while(s1[i+1]=='-' && i!=(len-2))
        {
            i += 2;
        }
        for (int c = current + 1; c <= s1[i]; c++)
        {
            s2[s2_ind++] = c;
        }
        if (s2_ind >= max_s2)
        {
            printf("expanded string exceeded s2 max length: %d", max_s2);
            exit(1);
        }
    }
}