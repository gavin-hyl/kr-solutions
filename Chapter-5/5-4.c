/**
 * @file 5-4.c
 * @author Gavin Hua
 * @brief 5-4: Write the function strend(s,t), which returns 1 if the string t
 * occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>
#include <string.h>

int strend(const char *, const char *);

int main(void)
{
    char *s = "this is a string";
    char *t = "ing";
    printf("%d\n", strend(s, t));
    return 0;
}

/**
 * @brief Checks whether one string is at the end of another
 *
 * @param s the string to be checked
 * @param t the target string
 * @return 1 if true, 0 if not
 */
int strend(const char *s, const char *t)
{
    int len_s = strlen(s);
    int len_t = strlen(t);
    while (*(s++ + len_s - len_t) == *(t++))
    {
        if (!*t)
        {   // *t is zero => t has ended.
            return 1;
        }
    }
    return 0;
}
