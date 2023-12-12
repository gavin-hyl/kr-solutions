/**
 * @file 8-1.c
 * @author Gavin Hua
 * @brief 8-1: Rewrite the program cat from Chapter 7 using read, write, open,
 * and close instead of their standard library equivalents. 
 * Perform experiments to determine the relative speeds of the two versions. 
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>  // BUFSIZ

int echo (int, int);

int main(int argc, char *argv[])
{
    char *prog = argv[0];
    int n;
    char buffer[BUFSIZ];
    int file;
    if (argc == 1)
    {
        echo(STDIN_FILENO, STDOUT_FILENO);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            file = open(argv[i], O_RDONLY, 0);
            echo(file, STDOUT_FILENO);
        }
    }
    return 0;
}

inline int echo(int fd1, int fd2)
{
    char buffer[BUFSIZ];
    int n;
    while((n=read(fd1, buffer, BUFSIZ)) > 0)
    {
        write(fd2, buffer, n);
    }
}