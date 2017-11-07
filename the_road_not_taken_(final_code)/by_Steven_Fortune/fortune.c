/*
Author - Steven Fortune
Implementation of his algorithm published in 1986 in paper "A sweepline algorithm for Voronoi diagrams".
*/

//original code has been modified to only compute delaunay triangulation
#
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

struct Site *readone();
struct Site *nextone();

int triangulate, sorted, plot, debug;
float xmin, xmax, ymin, ymax, deltax, deltay;
//modified to read from file obstacles.dat
FILE *in;

void delaunay() 
{	
system("echo -n > delaunay.dat");

int c;
struct Site *(*next)();

sorted = 0; triangulate = 0; plot = 0; debug = 0;
/*while((c=getopt(argc,argv,"dpst")) != EOF)
	switch(c) {
	case 'd': debug = 1;
		  break;
	case 's': sorted = 1;
		  break;
	case 't': triangulate = 1;
		  break;
	case 'p': plot = 1;
		  break;
		  };
*/
freeinit(&sfl, sizeof *sites);
if(sorted)
{	scanf("%d %f %f %f %f", &nsites, &xmin, &xmax, &ymin, &ymax);
	next = readone;
}
else 
{	readsites();
	next = nextone;
};

siteidx = 0;
geominit();
if(plot) plotinit();

//modified to compute only delaunay triangles
triangulate = 1;
compute_delaunay(triangulate, next); 
}

/* sort sites on y, then x, coord */
int scomp(s1,s2)
struct Point *s1,*s2;
{
	if(s1 -> y < s2 -> y) return(-1);
	if(s1 -> y > s2 -> y) return(1);
	if(s1 -> x < s2 -> x) return(-1);
	if(s1 -> x > s2 -> x) return(1);
	return(0);
}

/* return a single in-storage site */
struct Site *nextone()
{
struct Site *s;
for (;siteidx<nsites; siteidx+= 1)
{	if (siteidx==0 || sites[siteidx].coord.x!=sites[siteidx-1].coord.x 
		       || sites[siteidx].coord.y!=sites[siteidx-1].coord.y)
	{	siteidx += 1;
		return (&sites[siteidx-1]);
	};
};
return( (struct Site *)NULL);
}


/* read all sites, sort, and compute xmin, xmax, ymin, ymax */
readsites()
{
in = fopen("obstacles.dat", "r");
int i;

nsites=0;
sites = (struct Site *) myalloc(4000*sizeof *sites);
while(fscanf(in, "%f %f", &sites[nsites].coord.x, &sites[nsites].coord.y)!=EOF)
{	sites[nsites].sitenbr = nsites;
	sites[nsites].refcnt = 0;
	nsites += 1;
	if (nsites % 4000 == 0) 
		sites = (struct Site *) realloc(sites,(nsites+4000)*sizeof*sites);
}
qsort(sites, nsites, sizeof *sites, scomp);
xmin=sites[0].coord.x; 
xmax=sites[0].coord.x;
for(i=1; i<nsites; i+=1)
{	if(sites[i].coord.x < xmin) xmin = sites[i].coord.x;
	if(sites[i].coord.x > xmax) xmax = sites[i].coord.x;
};
ymin = sites[0].coord.y;
ymax = sites[nsites-1].coord.y;
fclose(in);
}

/* read one site */
struct Site *readone()
{
struct Site *s;

s = (struct Site *) getfree(&sfl);
s -> refcnt = 0;
s -> sitenbr = siteidx;
siteidx += 1;
if(scanf("%f %f", &(s->coord.x), &(s->coord.y)) == EOF)
	{
	return ((struct Site *) NULL );
	}
return(s);
}
