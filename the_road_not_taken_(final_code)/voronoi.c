/*
Authors: Rishabh Manoj, Anirudh Ravi, Penmetsa Murali Krishnam Raju, Samyak Upadhyay, Tadigadapa Abhiram and Nigel Steven Fernandez

Email IDs: Rishabh.Manoj@iiitb.org, Anirudh.Ravi@iiitb.org, raju.pmk@iiitb.org, Samyak.Upadhyay@iiitb.org, Abhiram.Tadigadapa@iiitb.org and NigelSteven.Fernandez@iiitb.org

Revision Number: 3

Date Modified: 22-12-2013
*/
#include "headers.h"

char file_line[100]; 
int i, j, k, **triangle_map, no_of_triangles, **triangle_graph, no_of_triangles;
float **point_map, circumcentre_x, circumcentre_y;
FILE *in, *out;

void build_point_map();
void build_triangle_map();
void build_triangle_graph();
void file_write();
int edge(int, int);
void circumcentre(int, int);


void voronoi()
	{
	/*
	Calls appropriate functions to build obstacle point map, delaunay triangle map, delaunay triangle graph and finally write the contents of the voronoi graph to voronoi.dat file.
	*/
	build_point_map();
	build_triangle_map();
	build_triangle_graph();
	file_write();
	}


void build_point_map()
	{
	/*
	Creates a 2D array which labels the various obstacle points with a unique index. Essentially creating a 'map' in which all values - 'obstacle points' are referenced by keys - 'unique number labels'.
	*/
	int no_of_obstacles;
	char x_string[20], y_string[20];
	float x, y;
	
	in = fopen("obstacles.dat", "r");
    if(in == NULL)
	    {
		fprintf(stderr, "Error in opening file.\n");
		exit(EXIT_FAILURE);
		}
		
	no_of_obstacles = 0;
	while(fgets(file_line, 100, in) != NULL)
		{
		no_of_obstacles += 1;
		}
	
	point_map = malloc(sizeof(float *) * no_of_obstacles);
	if(point_map == NULL)
	    {
		fprintf(stderr, "Out of memory");
	    exit(EXIT_FAILURE);
		}

	i = 0;
	while(i < no_of_obstacles)
		{
		point_map[i] = malloc(sizeof(*(point_map[i])) * 3);
		if(point_map[i] == NULL)
			{
			fprintf(stderr, "Out of memory");
			exit(EXIT_FAILURE);
			}
		i++;
		}
	
	fseek(in, 0, SEEK_SET);
	i = 0;
	while(i < no_of_obstacles)
		{
		fgets(file_line, 100, in);

		for(j = 0; j < 20; j++)
			{
			//initializing both strings to be 'empty'
			x_string[j] = 0;
			y_string[j] = 0;
			}

		//copying x coordinate string - 'upto space character'
		j = 0;
		k = 0;
		while(file_line[j] != ' ')
			{
			x_string[k] = file_line[j];
			j++;
			k++;
			}
		
		//copying y coordinate string - 'upto \n character'
		j += 1;
		k = 0;
		while(file_line[j] != '\n')
			{
			y_string[k] = file_line[j];
			j++;
			k++;
			}	
		
		//converting the strings to float variables
		x = atof(x_string);
		y = atof(y_string);
	
		//mapping the obstacle points
		point_map[i][0] = i;
		point_map[i][1] = x;
		point_map[i][2] = y;

		i++;
		}

	fclose(in);
	}


void build_triangle_map()
	{
	/*
	Creates a 2D array which labels the various delaunay triangles with a unique index. Essentially creating a 'map' in which all values - 'delaunay triangles' are referenced by keys - 'unique number labels'.
	*/
	char vertex1_string[20], vertex2_string[20], vertex3_string[20];
	int vertex1, vertex2, vertex3;

	in = fopen("delaunay.dat", "r");
    if(in == NULL)
	    {
		fprintf(stderr, "Error in opening file.\n");
		exit(EXIT_FAILURE);
		}
		
	no_of_triangles = 0;
	while(fgets(file_line, 100, in) != NULL)
		{
		no_of_triangles += 1;
		}
	
	triangle_map = malloc(sizeof(int *) * no_of_triangles);
	if(triangle_map == NULL)
	    {
		fprintf(stderr, "Out of memory");
	    exit(EXIT_FAILURE);
		}

	i = 0;
	while(i < no_of_triangles)
		{
		triangle_map[i] = malloc(sizeof(*(triangle_map[i])) * 4);
		if(triangle_map[i] == NULL)
			{
			fprintf(stderr, "Out of memory");
			exit(EXIT_FAILURE);
			}
		i++;
		}
	
	fseek(in, 0, SEEK_SET);
	i = 0;
	while(i < no_of_triangles)
		{
		fgets(file_line, 100, in);

		for(j = 0; j < 20; j++)
			{
			//initializing both strings to be 'empty'
			vertex1_string[j] = 0;
			vertex2_string[j] = 0;
			vertex3_string[j] = 0;
			}

		j = 0;
		k = 0;
		while(file_line[j] != ' ')
			{
			//copying vertex1 string - 'upto first space character'
			vertex1_string[k] = file_line[j];
			j++;
			k++;
			}

		j += 1;
		k = 0;
		while(file_line[j] != ' ')
			{
			//copying vertex2 string - 'upto second space character'
			vertex2_string[k] = file_line[j];
			j++;
			k++;
			}

		j += 1;
		k = 0;
		while(file_line[j] != '\n')
			{
			//copying vertex3 string - 'upto \n character'
			vertex3_string[k] = file_line[j];
			j++;
			k++;
			}	
		
		//converting vertices from string to integer variables
		vertex1 = atoi(vertex1_string);
		vertex2 = atoi(vertex2_string);
		vertex3 = atoi(vertex3_string);

		//mapping the delaunay triangles
		triangle_map[i][0] = i;
		triangle_map[i][1] = vertex1;
		triangle_map[i][2] = vertex2;
		triangle_map[i][3] = vertex3;

		i++;
		}
	
	fclose(in);
	}


void build_triangle_graph()
	{
	/*
	Builds pseudo voronoi graph - delaunay triangle graph in which the voronoi vertices are represented by the index of the dealaunay triangle in which they are contained.
	Scans through all pairs of delaunay triangles and updates the delaunay graph based on whether the pair of triangles have an egde or not.
	The graph is represented as a 2D array in which the first column of each row is a node and the remaining columns contain its adjacencent nodes.
	*/
	int index;
	
	triangle_graph = malloc(sizeof(int *) * no_of_triangles);
	if(triangle_graph == NULL)
	    {
		fprintf(stderr, "Out of memory");
	    exit(EXIT_FAILURE);
		}

	i = 0;
	while(i < no_of_triangles)
		{
		triangle_graph[i] = malloc(sizeof(*(triangle_graph[i])) * no_of_triangles + 1);
		if(triangle_graph[i] == NULL)
			{
			fprintf(stderr, "Out of memory");
			exit(EXIT_FAILURE);
			}
		i++;
		}
	
	for(i = 0; i < no_of_triangles; i++)
		{
		triangle_graph[i][0] = i;
		triangle_graph[i][1] = -1;
		}
	
	//scan through all delaunay triangle pairs
	for(i = 0; i < no_of_triangles; i++)
		for(j = i + 1; j < no_of_triangles; j++)
			//if the delaunay trianlge pair has an egde
			if(edge(i, j))
				{
				//then update the adjacency list of both triangles
				//updating first triangle's adjacency list
				for(k = 0; k < no_of_triangles; k++)
					if(triangle_graph[i][k] == -1)
						{
						index = k;
						break;
						}
				
				
				triangle_graph[i][index] = j;
				triangle_graph[i][index + 1] = -1;
				
				//updating second triangle's adjacency list
				for(k = 0; k < no_of_triangles; k++)
					if(triangle_graph[j][k] == -1)
						{
						index = k;
						break;
						}

				triangle_graph[j][index] = i;
				triangle_graph[j][index + 1] = -1;
				}
	}


int edge(int label1, int label2)
	{
	/*
	Returns 0 if the delaunay trianlges don't have an edge else 1.
	Checks for edges by checking if the delaunay triangles have 2 common vertices.
	*/
	int flag = 0, vertex1_triangle1, vertex2_triangle1, vertex3_triangle1, vertex1_triangle2, vertex2_triangle2, vertex3_triangle2;

	vertex1_triangle1 = triangle_map[label1][1];
	vertex2_triangle1 = triangle_map[label1][2];
	vertex3_triangle1 = triangle_map[label1][3];
	vertex1_triangle2 = triangle_map[label2][1];
	vertex2_triangle2 = triangle_map[label2][2];
	vertex3_triangle2 = triangle_map[label2][3];
	
	//checking for common vertices
	if(vertex1_triangle1 == vertex1_triangle2 || vertex1_triangle1 == vertex2_triangle2 || vertex1_triangle1 == vertex3_triangle2) 
		flag++;
	if(vertex2_triangle1 == vertex1_triangle2 || vertex2_triangle1 == vertex2_triangle2 || vertex2_triangle1 == vertex3_triangle2) 
		flag++;
	if(vertex3_triangle1 == vertex1_triangle2 || vertex3_triangle1 == vertex2_triangle2 || vertex3_triangle1 == vertex3_triangle2) 
		flag++;
	
	//if the number of common vertices of the pair of delaunay triangles is 2
	if(flag == 2)
		//then return True - 1
		return 1;

	return 0;
	}


void file_write()
	{
	/*
	Converts the pseudo voronoi graph - delaunay triangle graph to a complete voronoi graph.
	Finds the voronoi vertex of the delaunay triangle by finding its circumcentre.
	In place of each delaunay triangle prints its circumcentre thereby converting from pseudo to complete voronoi graph.
	*/
	out = fopen("graph.dat", "w");
	for(i = 0; i < no_of_triangles; i++)
		{
		j = 0;
		while(triangle_graph[i][j] != -1)
			{
			//updates coordinates of circumcentre for current delaunay triangle
			circumcentre(i, j);
			if(j == 0)
				fprintf(out, "%.2f %.2f", circumcentre_x, circumcentre_y); 
			else
				fprintf(out, " %.2f %.2f", circumcentre_x, circumcentre_y); 
			j++;
			}
		fprintf(out, "\n");
		}
	fclose(out);
	}


void circumcentre(i, j)
	{
	/*
	Finds the circumcentre of the delaunay triangle.
	*/
	int point1, point2, point3;
	float x1, x2, x3, y1, y2, y3, denominator;

	k = triangle_graph[i][j];
	point1 = triangle_map[k][1];
	point2 = triangle_map[k][2];
	point3 = triangle_map[k][3];
	
	x1 = point_map[point1][1];
	y1 = point_map[point1][2];
	x2 = point_map[point2][1];
	y2 = point_map[point2][2];
	x3 = point_map[point3][1];
	y3 = point_map[point3][2];

	//using cartesian formula for calculating the coordinates of the circumcentre
	denominator = 2 * ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));
	
	circumcentre_x = (((pow(x1, 2) + pow(y1, 2)) * (y2 - y3)) + ((pow(x2, 2) + pow(y2, 2)) * (y3 - y1)) + ((pow(x3, 2) + pow(y3, 2)) * (y1 - y2))) / denominator;

	circumcentre_y = (((pow(x1, 2) + pow(y1, 2)) * (x3 - x2)) + ((pow(x2, 2) + pow(y2, 2)) * (x1 - x3)) + ((pow(x3, 2) + pow(y3, 2)) * (x2 - x1))) / denominator;
	}
