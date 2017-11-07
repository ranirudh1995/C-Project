#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include"/usr/include/X11/Xlib.h"
void add_to_file(char *file,int x, int y )
    {
    FILE *append;
    append=fopen(file,"a");
    fprintf(append,"%d %d\n",x,y);
    fclose(append);
    }
void copy_file(char *file1,char *file2)
    {
    FILE *read,*write;
    int a,b;
    read=fopen(file1,"r");
    write=fopen(file2,"w");
    fscanf(read,"%d %d",&a,&b);
    while(!feof(read))
        {
        fprintf(write,"%d %d\n",a,b);
        fscanf(read,"%d %d",&a,&b);
        }
    fclose(read);
    fclose(write);
    }
void view_elements(char *file)
    {
    FILE *print;
    int i=1,x,y;
    print=fopen(file,"r");
    fscanf(print,"%d %d",&x,&y);
    fscanf(print,"%d %d",&x,&y);
    fscanf(print,"%d %d",&x,&y);
    while(!feof(print))
        {
        fprintf(stdout,"%d(%d,%d)\n",i,x,y);
        fscanf(print,"%d %d",&x,&y);
        i=i+1;
        }
    fclose(print);
    }

void remove_element(char *file1,char *file2,int x,int y)
    {
    int a,b;
    FILE *read,*write;
    read=fopen(file1,"r");
    write=fopen(file2,"w");
    fscanf(read,"%d %d",&a,&b);
    while(!feof(read))
        {
        if(x!=a || y!=b)
            {
            fprintf(write,"%d %d\n",a,b);
            }
        fscanf(read,"%d %d",&a,&b);
        }
    fclose(read);
    fclose(write);
    }


int main()
    {
	system("clear");
    int option=0,x,y;
    char k;
    fprintf(stdout,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tROBOT NAVIGATION USING VORONOI DIAGRAMS\n");
	char ch;
	scanf("%c", &ch);
	system("clear");
    fprintf(stdout,"Enter coordinates of initial point:\n");
    fscanf(stdin,"%d %d",&x,&y);
    add_to_file("points.dat",x,y);
	system("clear");
    fprintf(stdout,"Enter coordinates of final point:\n");
    fscanf(stdin,"%d %d",&x,&y);
    add_to_file("points.dat",x,y);
    int gd = DETECT,gm,count =4;
    initgraph(&gd,&gm,"c:\\Tc\\BGI");
	setbkcolor(WHITE);
	int flag = 0;
    while(option<4)
	    {
        system("clear");
    	fprintf(stdout,"Enter your choice:\n\n\n");
	    fprintf(stdout,"1.Add an obstacle\n\n2.Remove an obstacle\n\n3.View the Graph\n\n4.Proceed\n\n");
	    fscanf(stdin,"%d", &option);
	    if(option == 1)
		    {
			system("clear");
		    fprintf(stdout,"Enter x y cordinate:\n");
		    fscanf(stdin,"%d %d",&x,&y);
		    add_to_file("points.dat",x,y); 
            copy_file("points.dat","temp.dat");
            }
	    else if(option == 2)
		    {
            view_elements("temp.dat");
		    fprintf(stdout,"Enter x y coordinates of point to remove:\n");
		    fscanf(stdin,"%d %d",&x,&y);
		    remove_element("points.dat","temp.dat",x,y);
            copy_file("temp.dat","points.dat");
		    }
        else if(option == 3)
		    {
            cleardevice();
            FILE *read;
            read = fopen("temp.dat","r");
            fscanf(read,"%d %d",&x,&y);
		setcolor(GREEN);
            circle(x,y,2);
            fscanf(read,"%d %d",&x,&y);
		setcolor(GREEN);
            circle(x,y,2);
            while(!feof(read))
                {
                fscanf(read,"%d %d",&x,&y);
		setcolor(RED);
                circle(x,y,2);
                }
            getch();
            fclose(read);
            }
            system("clear");
        }
    closegraph();
    FILE *copy,*read;
    copy=fopen("obstacles.dat","w");
    read=fopen("points.dat","r");
    fscanf(read,"%d %d",&x,&y);
    fscanf(read,"%d %d",&x,&y);
    fscanf(read,"%d %d",&x,&y);
    while(!feof(read))
        {
        fprintf(copy,"%d %d\n",x,y);
    fscanf(read,"%d %d",&x,&y);
        }
    fclose(read);
    fclose(copy);

    system("clear");
    return 1;
    }
