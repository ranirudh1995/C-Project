/*
Author - Steven Fortune
Implementation of his algorithm published in 1986 in paper "A sweepline algorithm for Voronoi diagrams".
*/
#
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

freeinit(fl, size)
struct	Freelist *fl;
int	size;
{
fl -> head = (struct Freenode *) NULL;
fl -> nodesize = size;
}

char *getfree(fl)
struct	Freelist *fl;
{
int i; struct Freenode *t;
if(fl->head == (struct Freenode *) NULL)
{	t =  (struct Freenode *) myalloc(sqrt_nsites * fl->nodesize);
	for(i=0; i<sqrt_nsites; i+=1) 	
		makefree((struct Freenode *)((char *)t+i*fl->nodesize), fl);
};
t = fl -> head;
fl -> head = (fl -> head) -> nextfree;
return((char *)t);
}



makefree(curr,fl)
struct Freenode *curr;
struct Freelist *fl;
{
curr -> nextfree = fl -> head;
fl -> head = curr;
}

int total_alloc;
char *myalloc(n)
unsigned n;
{
char *t;
if ((t=malloc(n)) == (char *) 0)
{    fprintf(stderr,"Insufficient memory processing site %d (%d bytes in use)\n",
		siteidx, total_alloc);
     exit(1);
};
total_alloc += n;
return(t);
}
