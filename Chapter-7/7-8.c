/*
    Write a program to print a set of files, starting each new one on a new page,
    with a title and a running page count for each file.
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINE 100
#define PAGELINES 10

void pagebreak(void);

int main(int argc, char const *argv[])
{
    char line[MAXLINE];
    int pagelines = 0;
    clock_t start, end;

    start = clock();
	if (argc == 1)
	{
		printf("Usage: print files.\n");
		return 0;
	}
    while (*++argv != NULL)
    {   
        pagebreak();
        FILE *fp;
        fp = fopen(*argv, "r");
        while (fgets(line, MAXLINE, fp))
        {   // print all lines in the file
            pagelines++;
            printf(line);
            if (pagelines % PAGELINES == 0)
            {
                pagebreak();
                pagelines = 0;
            }
        }
        while (pagelines % PAGELINES != 0)
        {   // pad the rest of the page
            printf("\n");
            pagelines++;
        }
        fclose(fp);
    }
    end = clock();
    printf("%d", end-start);
    return 0;
}

void pagebreak()
{
    static int npage = 1;
    printf("----------Page %d----------\n", npage); 
    npage++;
}