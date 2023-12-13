/**
 * @file 8-5.c
 * @author Gavin Hua
 * @brief Exercise 8-5.
 * 
 * Modify the fsize program to print the other information contained in the 
 * inode entry.
 */

#define NAME_MAX 14 /* longest filename component; system-dependent*/

typedef struct
{                            /* portable directory entry */
    long ino;                /* inode number */
    char name[NAME_MAX + 1]; /* name + '\0' terminator */
} Dirent;

typedef struct
{             /* minimal DIR: no buffering, etc. */
    int fd;   /* file descriptor for the directory */
    Dirent d; /* the directory entry */
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

#include <stdio.h>
#include <string.h>
#include <fcntl.h>     /* flags for read and write */
#include <sys/types.h> /* typedefs */
#include <sys/stat.h>  /* structure returned by stat */

void fsize(char *);

int main(int argc, char **argv)
{
    if (argc == 1) /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/**
 * @brief Prints information associated with the file
 * 
 * @param name the file path
 */
void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    {
        if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        {
            dirwalk(name, fsize);
        }
        printf("Size: %8ld %s\n", stbuf.st_size, name);
        printf("Mode: %8o %s\n", stbuf.st_mode, name);
        printf("User: %8u %s\n", stbuf.st_uid, name);
    }
}

#define MAX_PATH 1024
/**
 * @brief Applies a functional to all files once in a directory recursively.
 * 
 * @param dir the directory
 * @param fcn the function
 */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
        {
            continue; /* skip self and parent */
        }
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
        {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        }
        else
        {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}