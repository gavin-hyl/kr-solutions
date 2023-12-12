// Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.

#include <stdio.h>

void stringcat(char *s, char *t)
{   
    while(*(++s));
    while(*s++ = *t++);
}

int main(int argc, char const *argv[])
{
    char s[] = "hello ", *ps;
    char t[] = "world!", *pt;
    ps = s;
    pt = t;
    stringcat(ps, pt);
    printf(s);
    return 0;
}