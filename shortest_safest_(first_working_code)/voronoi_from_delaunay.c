#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char line[100]; 
int i, j, k, **triangle_map, no_of_triangles, **triangle_graph, no_of_triangles;
float **point_map, circumcentre_x, circumcentre_y;
FILE *in, *out;

void build_point_map();
void build_triangle_map();
void build_triangle_graph();
void write();
int edge(int, int);
void circumcentre(int, int);


int main()
	{
	build_point_map();
	build_triangle_map();
	build_triangle_graph();
	write();
	
	return 0;
	}


void build_point_map()
	{
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
	while(fgets(line, 100, in) != NULL)
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
		fgets(line, 100, in);

		for(j = 0; j < 20; j++)
			{
			x_string[j] = 0;
			y_string[j] = 0;
			}


		j = 0;
		k = 0;
		while(line[j] != ' ')
			{
			x_string[k] = line[j];
			j++;
			k++;
			}

		j += 1;
		k = 0;
		while(line[j] != '\n')
			{
			y_string[k] = line[j];
			j++;
			k++;
			}	
		
		x = atof(x_string);
		y = atof(y_string);

		point_map[i][0] = i;
		point_map[i][1] = x;
		point_map[i][2] = y;

		i++;
		}

	fclose(in);
	}


void build_triangle_map()
	{
	char vertex1_string[20], vertex2_string[20], vertex3_string[20];
	int vertex1, vertex2, vertex3;

	in = fopen("delaunay.dat", "r");
    if(in == NULL)
	    {
		fprintf(stderr, "Error in opening file.\n");
		exit(EXIT_FAILURE);
		}
		
	no_of_triangles = 0;
	while(fgets(line, 100, in) != NULL)
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
		fgets(line, 100, in);

		for(j = 0; j < 20; j++)
			{
			vertex1_string[j] = 0;
			vertex2_string[j] = 0;
			vertex3_string[j] = 0;
			}

		j = 0;
		k = 0;
		while(line[j] != ' ')
			{
			vertex1_string[k] = line[j];
			j++;
			k++;
			}

		j += 1;
		k = 0;
		while(line[j] != ' ')
			{
			vertex2_string[k] = line[j];
			j++;
			k++;
			}

		j += 1;
		k = 0;
		while(line[j] != '\n')
			{
			vertex3_string[k] = line[j];
			j++;
			k++;
			}	
		
		vertex1 = atof(vertex1_string);
		vertex2 = atof(vertex2_string);
		vertex3 = atof(vertex3_string);

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
	//why can't I declare it as a global variable?
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

	for(i = 0; i < no_of_triangles; i++)
		for(j = i + 1; j < no_of_triangles; j++)
			if(edge(i, j))
				{
				for(k = 0; k < no_of_triangles; k++)
					if(triangle_graph[i][k] == -1)
						{
						index = k;
						break;
						}
				
				
				triangle_graph[i][index] = j;
				triangle_graph[i][index + 1] = -1;

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
	int flag = 0, vertex1_triangle1, vertex2_triangle1, vertex3_triangle1, vertex1_triangle2, vertex2_triangle2, vertex3_triangle2;

	vertex1_triangle1 = triangle_map[label1][1];
	vertex2_triangle1 = triangle_map[label1][2];
	vertex3_triangle1 = triangle_map[label1][3];
	vertex1_triangle2 = triangle_map[label2][1];
	vertex2_triangle2 = triangle_map[label2][2];
	vertex3_triangle2 = triangle_map[label2][3];

	if(vertex1_triangle1 == vertex1_triangle2 || vertex1_triangle1 == vertex2_triangle2 || vertex1_triangle1 == vertex3_triangle2) 
		flag++;
	if(vertex2_triangle1 == vertex1_triangle2 || vertex2_triangle1 == vertex2_triangle2 || vertex2_triangle1 == vertex3_triangle2) 
		flag++;
	if(vertex3_triangle1 == vertex1_triangle2 || vertex3_triangle1 == vertex2_triangle2 || vertex3_triangle1 == vertex3_triangle2) 
		flag++;

	if(flag == 2)
		return 1;

	return 0;
	}


void write()
	{
	out = fopen("graph.dat", "w");
	for(i = 0; i < no_of_triangles; i++)
		{
		j = 0;
		while(triangle_graph[i][j] != -1)
			{
			circumcentre(i, j);
			if(j == 0)
				fprintf(out, "%.2f %.2f", circumcentre_x, circumcentre_y); 
			else
				fprintf(out, " %.2f %.2f", circumcentre_x, circumcentre_y); 
			j++;
			}
		fprintf(out, "\n");
		}
	close(out);
	}


void circumcentre(i, j)
	{
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

	denominator = 2 * ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));

	circumcentre_x = (((pow(x1, 2) + pow(y1, 2)) * (y2 - y3)) + ((pow(x2, 2) + pow(y2, 2)) * (y3 - y1)) + ((pow(x3, 2) + pow(y3, 2)) * (y1 - y2))) / denominator;

	circumcentre_y = (((pow(x1, 2) + pow(y1, 2)) * (x3 - x2)) + ((pow(x2, 2) + pow(y2, 2)) * (x1 - x3)) + ((pow(x3, 2) + pow(y3, 2)) * (x2 - x1))) / denominator;
	}
