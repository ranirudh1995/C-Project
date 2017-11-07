/*
Authors: Rishabh Manoj, Anirudh Ravi, Penmetsa Murali Krishnam Raju, Samyak Upadhyay, Tadigadapa Abhiram and Nigel Steven Fernandez

Email IDs: Rishabh.Manoj@iiitb.org, Anirudh.Ravi@iiitb.org, raju.pmk@iiitb.org, Samyak.Upadhyay@iiitb.org, Abhiram.Tadigadapa@iiitb.org and NigelSteven.Fernandez@iiitb.org

Revision Number: 6

Date Modified: 22-12-2013
*/
#include "/usr/include/X11/Xlib.h"
#include "headers.h"

void add_to_file(char *file, float x, float y );
void copy_file(char *file1, char *file2);
void view_elements(char *file);
void remove_element(char *file1, char *file2, float x, float y);
void create_obstacles_file();

float x, y;

void input()
    {
	/*
	Inputs initial point, final point and obstacles points using the graphics library of C.
	Main menu has options to add, remove and view obstacle points.
	*/
    int option = 0, i = 1;
    char k, ch;
	
	//creating empty files points.dat, obstacles.dat and temp.dat
	//truncating already existing files
	system("echo -n > obstacles.dat");
	system("echo -n > points.dat");
	system("echo -n > temp.dat");

	system("clear");
    fprintf(stdout, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tROBOT NAVIGATION USING VORONOI DIAGRAMS\n");
	scanf("%c", &ch);

	system("clear");
    fprintf(stdout, "Enter coordinates of initial point:\n");
    fscanf(stdin, "%f %f", &x, &y);
    add_to_file("points.dat", x, y);
	
	system("clear");
    fprintf(stdout, "Enter coordinates of final point:\n");
    fscanf(stdin, "%f %f", &x, &y);
    add_to_file("points.dat", x, y);

	//initializing graphics
    int gd = DETECT, gm, count = 4;
    initgraph(&gd, &gm, "c:\\Tc\\BGI");
	setbkcolor(WHITE);

	//delay() used to handle graphics message
	delay(1000);

	while(i)
	    {
        system("clear");
    	fprintf(stdout, "Enter your choice:\n\n");
	    fprintf(stdout, "1 - Add an obstacle\n2 - Remove an obstacle\n3 - View the graph\n4 - Proceed\n\n");
	    fscanf(stdin, "%d", &option);
		switch(option)
			{
			case 1:
				system("clear");
			    fprintf(stdout, "Enter coordinates of obstacle:\n");
			    fscanf(stdin, "%f %f", &x, &y);
			    add_to_file("points.dat", x, y); 
				copy_file("points.dat", "temp.dat");
				break;

		    case 2:
	            view_elements("temp.dat");
			    fprintf(stdout,"Enter coordinates of obstacle to remove:\n");
			    fscanf(stdin,"%f %f", &x, &y);
				remove_element("points.dat", "temp.dat", x, y);
	            copy_file("temp.dat", "points.dat");
			    break;

	        case 3:
		        cleardevice();
			    FILE *read;

				read = fopen("temp.dat", "r");
	            fscanf(read, "%f %f", &x, &y);
				setcolor(BLUE);
			    circle(x, y, 2);
	            fscanf(read, "%f %f", &x, &y);
				setcolor(BLUE);
				circle(x, y, 2);
	            while(!feof(read))
		            {
			        fscanf(read, "%f %f", &x, &y);
					setcolor(RED);
				    circle(x, y, 2);
					}
	            getch();

		        fclose(read);
			    break;

			default:
				closegraph();
				system("clear");
				system("rm temp.dat");
				create_obstacles_file();
				i = 0;
			}
		}
    }


void add_to_file(char *file, float x, float y )
    {
	/*
	Adds coordinate values to a file.
	*/
    FILE *append;

    append = fopen(file, "a");
    fprintf(append, "%f %f\n", x, y);

    fclose(append);
    }


void copy_file(char *file1, char *file2)
    {
	/*
	Copies the contents of one file to another.
	*/
    FILE *read, *write;
    int a, b;

    read = fopen(file1, "r");
    write = fopen(file2, "w");
    fscanf(read, "%f %f", &x, &y);
    while(!feof(read))
        {
        fprintf(write, "%f %f\n", x, y);
        fscanf(read, "%f %f", &x, &y);
        }

    fclose(read);
    fclose(write);
    }


void view_elements(char *file)
    {
	/*
	Displays coordinates of obstacle points.
	*/
    FILE *read;
    int i = 1;

    read = fopen(file, "r");
    fscanf(read, "%f %f", &x, &y);
    fscanf(read, "%f %f", &x, &y);
    fscanf(read, "%f %f", &x, &y);
    while(!feof(read))
        {
        fprintf(stdout, "%d. (%f, %f)\n", i, x, y);
        fscanf(read, "%f %f", &x, &y);
        i += 1;
        }

    fclose(read);
    }


void remove_element(char *file1, char *file2, float x, float y)
    {
	/*
	Removes a specific obstacle point.
	Logic - Copy all obstacle points to a temporary file except the one to be removed.
	*/
    float a, b;
    FILE *read, *write;

    read = fopen(file1, "r");
    write = fopen(file2, "w");
    fscanf(read, "%f %f", &a, &b);
    while(!feof(read))
        {
        if(x != a || y != b)
            fprintf(write, "%f %f\n", a, b);
        fscanf(read, "%f %f", &a, &b);
        }

    fclose(read);
    fclose(write);
    }


void create_obstacles_file()
	{
	/*
	Creates obstacles.dat file - same as points.dat file without initial and final point.
	*/
    FILE *copy, *read;
    copy = fopen("obstacles.dat", "w");
    read = fopen("points.dat", "r");

    fscanf(read, "%f %f", &x, &y);
    fscanf(read, "%f %f", &x, &y);
    fscanf(read, "%f %f", &x, &y);

    while(!feof(read))
        {
        fprintf(copy, "%f %f\n", x, y);
		fscanf(read, "%f %f", &x, &y);
        }

    fclose(read);
    fclose(copy);
	}
