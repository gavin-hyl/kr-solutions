/**
 * @file 8-4.c
 * @author Gavin Hua
 * @brief 8-4: Design and write _flushbuf, fflush, and fclose.
 */

#include <unistd.h>
#include <stdlib.h>

/* from stdlib.h */
#ifdef NULL
#undef NULL
#endif

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

#pragma pack(1) /* reduces the size of the __flags struct from 4 bytes to 1 */
struct _fflags
{
    unsigned int read : 1;  /* file open for reading */
    unsigned int write : 1; /* file open for writing */
    unsigned int unbuf : 1; /* file is unbuffered */
    unsigned int eof : 1;   /* EOF has occurred on this file */
    unsigned int err : 1;   /* error occurred on this file */
};

typedef struct _iobuf
{
    int cnt;              /* characters left in buffer */
    char *ptr;            /* next character position in buffer */
    char *buf;            /* location of buffer */
    struct _fflags flags; /* mode of file access */
    int fd;               /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags
{
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0                  \
                     ? (unsigned char)*(p)->ptr++ \
                     : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0         \
                        ? *(p)->ptr++ = (x) \
                        : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#define PERMS 0666 /* RW for owner, group, others */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    {
        return NULL; /* invalid mode */
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    {
        if ((fp->flags.read & fp->flags.write) == 0)
        {
            break; /* found free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) /* no free slots */
    {
        return NULL;
    }
    if (*mode == 'w')
    {
        fd = creat(name, PERMS);
    }
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
        {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    }
    else
    {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) /* couldn't access name */
    {
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->buf = NULL;
    if (*mode == 'r')
    {
        fp->flags.read = 1;
    }
    else
    {
        fp->flags.write = 1;
    }

    return fp;
}

/**
 * @brief Allocate and fill input buffer
 *
 * @param fp the file pointer to fill the buffer for
 * @return position of the next character in the file
 */
int _fillbuf(FILE *fp)
{
    int bufsize;
    if (fp->flags.read & !fp->flags.eof)
    {
        return EOF;
    }
    bufsize = (fp->flags.unbuf) ? 1 : BUFSIZ;

    if (fp->buf == NULL) /* no buffer yet */
    {
        if ((fp->buf = (char *)malloc(bufsize)) == NULL)
        {
            return EOF; /* can't get buffer */
        }
    }

    fp->ptr = fp->buf;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
        {
            fp->flags.eof = 1;
        }
        else
        {
            fp->flags.err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/**
 * @brief flushes the I/O (write) buffer associated with the file
 *
 * @param c the current character
 * @param fp the file
 * @return number of characters written
 */
int _flushbuf(int c, FILE *fp)
{
    int num_written, bufsize;
    unsigned char uc = c;

    if (!fp->flags.write || fp->flags.eof || fp->flags.err)
    {
        return EOF;
    }

    if (fp->buf == NULL && fp->flags.unbuf == 0)
    {
        if ((fp->buf = malloc(BUFSIZ)) == NULL)
        {
            return EOF;
        }
        else
        {
            fp->ptr = fp->buf;
            fp->cnt = BUFSIZ - 1;
        }
    }

    if (fp->flags.unbuf)
    {
        fp->ptr = fp->buf = NULL;
        fp->cnt = 0;
        if (c == EOF)
        {
            return EOF;
        }
        num_written = write(fp->fd, &uc, 1);
        bufsize = 1;
    }
    else
    {
        if (c != EOF)
        {
            *(fp)->ptr = uc;
        }
        bufsize = (int)(fp->ptr - fp->buf + 1);
        num_written = write(fp->fd, fp->buf, bufsize);
        fp->ptr = fp->buf;
        fp->cnt = BUFSIZ - 1;
    }

    if (num_written == bufsize)
    {
        return c;
    }
    else
    {
        return EOF;
    }
}

int fflush(FILE *fp)
{
    if (fp == NULL || !fp->flags.write)
    {
        return EOF;
    }
    _flushbuf(EOF, fp);
    return fp->flags.err * EOF;
}

int fclose(FILE *fp)
{
    if (fp == NULL)
    {
        return EOF;
    }

    fflush(fp);

    fp->fd = fp->cnt = 0;
    fp->ptr = NULL;
    fp->flags.read = fp->flags.write = fp->flags.unbuf =
        fp->flags.eof = fp->flags.err = 0;
    if (fp->buf)
    {
        free(fp->buf);
        fp->buf = NULL;
    }

    return close(fp->fd);
}

int fseek(FILE *fp, long offset, int origin)
{
    if (!fp->flags.unbuf && fp->buf != NULL)
    {
        if (fp->flags.write)
        {
            if (fflush(fp)) // flush buffer and directly go to lseek
            {
                return EOF;
            }
        }
        if (fp->flags.read)
        {
            if (origin == 1)
            {
                if (offset >= 0 && offset <= fp->cnt)
                {
                    fp->cnt -= offset;
                    fp->ptr += offset;
                    fp->flags.eof = 0;
                    return 0;
                }
                offset -= fp->cnt;
            }
            fp->cnt = 0;
            fp->ptr = fp->buf;
        }
    }
    if (lseek(fp->fd, offset, origin) == EOF)
    {
        fp->flags.eof = 1;
        return EOF;
    }
    return 0;
}

FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, {1, 0, 0, 0, 0}, 0}, /* stdin */
    {0, (char *)0, (char *)0, {0, 1, 0, 0, 0}, 1}, /* stdout */
    {0, (char *)0, (char *)0, {0, 1, 1, 0, 0}, 2}  /* stderr */
};