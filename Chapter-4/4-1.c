// Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none.

#include<stdio.h>
#include<string.h>

int strindex(const char[], const char[]);

int main()
{
    char s[] = "12345123456789";
    char t[] = "123";
    
    printf("%d\n", strindex(s, t));
    return 0;
}

/*
    Returns the position of the rightmost occurrence of t in s, 
    or -1 if there is none.
*/
int strindex(const char s[], const char t[]){
    int s_len = strlen(s);
    int t_len = strlen(t);

    for(int i = s_len - 1; i >= 0; i--){
        if(s[i] == t[0])
        {
            int j = 1;
            for(; (j < t_len) && (s[i+j] == t[j]); j++);
            if(j == t_len)  // the entirety of string t has been found.
            {
                return i;
            }
        }
    }
    return -1;
}