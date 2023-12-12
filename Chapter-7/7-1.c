/* 
	Write a program that converts upper case to lower or lower case to upper,
	depending on the name it is invoked with, as found in argv[0]. 
	? (I'm supposing this means argv[1]. One could also create two files 7-1u and
	? 7-1l, but that would be too boring.)
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int lower = 0, c;
    if(argc==2)
    {
        lower = !strcmp("-l", argv[1]);
    }

	if (lower)
	{
		while ((c=getchar()) != EOF)
		{
			putchar(tolower(c));
		}
	}
	else
	{
		while ((c=getchar()) != EOF)
		{
			putchar(toupper(c));
		}
	}
	return 0;
}
