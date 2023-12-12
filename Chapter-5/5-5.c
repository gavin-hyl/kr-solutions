// 5.5 Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. 
// For example, strncpy(s,t,n) copies at most n characters of t to s.

#include <stdio.h>

void loc_strncpy(char *, char *, int);
void loc_strncat(char *, char *, int);
int loc_strncmp(char *, char *, int);

int main()
{
    char str1[100] = "abcdefg";
    char str2[100] = "1234567";
    char str3[100] = "abcdhij";
    loc_strncat(str1, str2, 3);
    printf("result of strncmp: %d\n", loc_strncmp(str1, str3, 2));
    printf(str1);
}

void loc_strncpy(char *s, char *t, int n)
{
    // check p < n before copying character
    for (int p = 0; (p < n) && (*(s+p) = *(t+p)); p++);
}

void loc_strncat(char *s, char *t, int n)
{
    while(*s++) ;
    s--;    // this allows the for loop to overwrite the '\0' first
    for(int p = 0; (p < n) && (*(s+p) = *(t+p)); p++);    
}

int loc_strncmp(char *s, char *t, int n)
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