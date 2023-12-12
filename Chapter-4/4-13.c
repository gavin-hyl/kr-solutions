// Write a recursive version of the function reverse(s), which reverses the string s in place.

#include<stdio.h>
#include<string.h>

void reverse(char s[]){
    static int ind;
    if(ind != (strlen(s)/2))
    {
        char temp = s[strlen(s)-1-ind];
        s[strlen(s)-1-ind] = s[ind];
        s[ind] = temp;
        ind++;
        reverse(s);
    }
}

int main(void)
{
    char s[] = "12345";
    reverse(s);
    printf(s);
    return 0;
}