/**
 * @file 5-5.c
 * @author Gavin Hua
 * @brief 5.5: Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument 
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 */

#include <stdio.h>

void my_strncpy(char *, char *, int);
void my_strncat(char *, char *, int);
int my_strncmp(char *, char *, int);

int main()
{
    char str1[100] = "abcdefg";
    char str2[100] = "1234567";
    char str3[100] = "abcdhij";
    my_strncat(str1, str2, 3);
    printf("result of strncmp: %d\n", my_strncmp(str1, str3, 2));
    printf(str1);
}

/**
 * @brief Copies at most n characters from t to s
 * 
 * @param s the target string
 * @param t the string to be copied
 * @param n the copying limit
 */
void my_strncpy(char *s, char *t, int n)
{
    for (int p = 0; (p < n) && (*(s+p) = *(t+p)); p++);
}

/**
 * @brief Concatenates at most n characters of t to the end of s
 * 
 * @param s the base string
 * @param t the string to be copied
 * @param n the concat limit
 */
void my_strncat(char *s, char *t, int n)
{
    while(*s++) ;
    s--;    // this allows the for loop to overwrite the '\0' first
    for(int p = 0; (p < n) && (*(s+p) = *(t+p)); p++);    
}

/**
 * @brief Compares at most n characters of s and t
 * 
 * @param s the first string to be compared
 * @param t the second string to be compared
 * @param n the comparison limit
 */
int my_strncmp(char *s, char *t, int n)
{
    int p = 0;
    for (; (p < n) && *(s+p) == *(t+p); p++)
    {
        if (*s == '\0')
        {
            return 0;
        }       
    }
    return *(s+p) - *(t+p);
}