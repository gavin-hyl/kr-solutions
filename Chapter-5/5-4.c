// Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.

#include <stdio.h>
#include <string.h>

int strend(const char *s, const char *t)
{
    int len_s = strlen(s);
    int len_t = strlen(t);
    while (*(s++ + len_s - len_t) == *(t++))
    {
        if(! *t)
        {   // *t is zero => t has ended.
            return 1;
        }
    }
    return 0;
}


int main(int argc, const char *argv[])
{
    char *s = "this is a string";
    char *t = "ing";
    printf("%d\n", strend(s, t));     // should return 1;
    return 0;
}
