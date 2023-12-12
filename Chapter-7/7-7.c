/* 
    Modify the pattern finding program of Chapter 5 to take its input from a set of
    named files or, if no files are named as arguments, from the standard input. 
    Should the file name be printed when a matching line is found? (Yes)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

int main(int argc, char const *argv[])
{
    char line[MAXLINE], pattern[MAXLINE];
    int nline = 0;

	if (argc == 1)
	{
		printf("Usage: find pattern.\n");
		return 1;
	}
	strcpy(pattern, *++argv);
    if (argc == 2)
    {
        while (fgets(line, MAXLINE, stdin) != NULL)
        {
            nline++;
            if (strstr(line, pattern))
            {
                printf("found pattern \"%s\" on line %d\n", pattern, nline);
            }
        }
    }
    else
    {
        while (*++argv != NULL)
        {   
            nline = 0;
            FILE *fp;
            fp = fopen(*argv, "r"); 
            while (fgets(line, MAXLINE, fp))
            {
                nline++;
                if (strstr(line, pattern))
                {
                    printf("found pattern \"%s\" on line %d of file %s\n", pattern, nline, *argv);
                }
            }
            fclose(fp);
        }
    }
    return 0;
}