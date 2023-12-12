/**
 * @file 8-8.c
 * @author Gavin Hua
 * @brief 8-8: Write a routine bfree(p,n) that will free any arbitrary block p 
 * of n characters into the free list maintained by malloc and free. By using
 * bfree, a user can add a static or external array to the free list at any time. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef long Align; /* alignment to long boundary*/

typedef union header
{
    struct
    {
        union header *next; /* next block */
        unsigned int size;  /* size of this block, in terms of units */
    } info;
    Align _; /* force alignment of blocks */
} Header;

static Header base;           /* empty list */
static Header *free_p = NULL; /* start of free list */
static Header *more_mem(unsigned);
void my_free(void *);
void *my_malloc(unsigned);
void *my_calloc(unsigned, unsigned);
void bfree(void *, unsigned);

void *my_malloc(unsigned n_bytes)
{
    Header *p, *prev_p;
    unsigned int n_units;

    /* one unit is the size of a header union */
    n_units = (n_bytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prev_p = free_p) == NULL) 
    {   /* no free list yet, initialize base */
        base.info.next = free_p = prev_p = &base;
        base.info.size = 0;
    }
    p = prev_p->info.next;
    while (1)
    {
        if (p->info.size >= n_units)
        {
            if (p->info.size == n_units)
            {
                prev_p->info.next = p->info.next;
            }
            else
            {
                p->info.size -= n_units;
                p += p->info.size;
                p->info.size = n_units;
            }
            free_p = prev_p;
            return (void *)(p + 1);
        }
        if (p == free_p)
        {
            if ((p = more_mem(n_units)) == NULL)
            {
                return NULL;
            }
        }
        prev_p = p;
        p = p->info.next;
    }
}

#define N_ALLOC 1024 /* minimum number of units to request */

static Header *more_mem(unsigned n_units)
{
    char *cp;
    Header *up;

    if (n_units < N_ALLOC)
    {
        n_units = N_ALLOC;
    }

    cp = sbrk(n_units * sizeof(Header));

    if (cp == (char *)-1) /* no space at all */
    {
        return NULL;
    }

    up = (Header *)cp;
    up->info.size = n_units;

    my_free((void *)(up + 1));

    return free_p;
}

/* free: put block ap in free list */
void my_free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap - 1; /* point to block header */
    for (p = free_p; !(bp > p && bp < p->info.next); p = p->info.next)
    {
        if (p >= p->info.next && (bp > p || bp < p->info.next))
        {   /* freed block at start or end of arena */
            break;
        }
    }
    if (bp + bp->info.size == p->info.next)
    { /* join to upper nbr */
        bp->info.size += p->info.next->info.size;
        bp->info.next = p->info.next->info.next;
    }
    else
    {
        bp->info.next = p->info.next;
    }
    if (p + p->info.size == bp)
    { /* join to lower nbr */
        p->info.size += bp->info.size;
        p->info.next = bp->info.next;
    }
    else
    {
        p->info.next = bp;
    }
    free_p = p;
}

void *my_calloc(unsigned n_obj, unsigned n_bytes)
{
    char *ret_p = malloc(n_obj * n_bytes);
    if (ret_p == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < n_obj * n_bytes; i++)
    {
        ret_p[i] = 0;
    }
    return (void *) ret_p;
}

void bfree(void *block, unsigned n_bytes)
{
    if (block == NULL || n_bytes < 0)
    {
        return;
    }
    Header *header_p = (Header *) block;
    unsigned n_units = n_bytes / sizeof(Header);
    if (free_p == NULL)
    {   /* no free list yet, initialize base */
        base.info.next = free_p = &base;
        base.info.size = 0;
    }
    header_p->info.size = n_units;
    my_free((void *) (header_p + 1));
}

int main(int argc, char const *argv[])
{
    printf("%p\n", free_p);
    char *p1 = my_malloc(1024 * sizeof(Header));
    printf("%p\n", free_p);
    char *p2 = my_malloc(2048 * sizeof(Header));
    printf("%p\n", free_p);
    return 0;
}
