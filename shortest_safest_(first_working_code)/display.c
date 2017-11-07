#include<stdio.h>
#include<math.h>
#include<graphics.h>
int main()
	{
	FILE *point;
	FILE *obst;
	point = fopen("path.dat","r");
	obst = fopen("obstacles.dat","r");
	float xin,yin;
	float xfin,yfin;
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	setbkcolor(WHITE);
	fscanf(point,"%f %f",&xin,&yin);
	setcolor(BLUE);
	circle(xin,yin,2);
	fscanf(point,"%f %f",&xfin,&yfin);
	setcolor(BLACK);
	line(xin,yin,xfin,yfin);
	//setcolor(BLUE);
	//circle(xfin,yfin,2);
	while(!(feof(point)))
		{
		fscanf(point,"%f %f",&xin,&yin);
		//setcolor(BLUE);
		//circle(xin,yin,2);
		setcolor(BLACK);
		line(xfin,yfin,xin,yin);
		xfin = xin;
		yfin = yin;
		}
	fclose(point);
	setcolor(BLUE);
	circle(xfin,yfin,2);
	float obsx,obsy;
	fscanf(obst,"%f %f",&obsx,&obsy);
	while(!feof(obst))
		{
		setcolor(RED);
		circle(obsx,obsy,3);
		fscanf(obst,"%f %f",&obsx,&obsy);
		}	
	getch();
	closegraph();
	return 1;
	}
