/*
Authors: Rishabh Manoj, Anirudh Ravi, Penmetsa Murali Krishnam Raju, Samyak Upadhyay, Tadigadapa Abhiram and Nigel Steven Fernandez

Email IDs: Rishabh.Manoj@iiitb.org, Anirudh.Ravi@iiitb.org, raju.pmk@iiitb.org, Samyak.Upadhyay@iiitb.org, Abhiram.Tadigadapa@iiitb.org and NigelSteven.Fernandez@iiitb.org

Revision Number: 5

Date Modified: 22-12-2013
*/
#include "headers.h"


void display()
	{
	/*
	Displays the initial and final points in Blue, obstacle points in Red and the shortest safest path with Black lines joining the vertices of the voronoi graph.
	*/
	FILE *point, *obst;
	float xin, yin, obsx, obsy, xfin, yfin;
	int gd = DETECT, gm;
	
	//initializing graphics
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	setbkcolor(WHITE);

	//reading coordinates of safest_shortest path from appropriate files
	point = fopen("path.dat", "r");
	obst = fopen("obstacles.dat", "r");
	
	//displaying initial point
	fscanf(point, "%f %f", &xin, &yin);
	setcolor(BLUE);
	circle(xin, yin, 2);

	//displaying lines joining the nodes of the safest_shortest path
	fscanf(point, "%f %f", &xfin, &yfin);
	setcolor(BLACK);
	line(xin, yin, xfin, yfin);
	while(!(feof(point)))
		{
		fscanf(point, "%f %f", &xin, &yin);
		setcolor(BLACK);
		line(xfin, yfin, xin, yin);
		xfin = xin;
		yfin = yin;
		}

	fclose(point);

	//displaying final point
	setcolor(BLUE);
	circle(xfin,yfin,2);
	
	//displaying obstacle points
	fscanf(obst,"%f %f",&obsx,&obsy);
	while(!feof(obst))
		{
		setcolor(RED);
		circle(obsx,obsy,3);
		fscanf(obst,"%f %f",&obsx,&obsy);
		}
	getch();
	
	closegraph();
	}
