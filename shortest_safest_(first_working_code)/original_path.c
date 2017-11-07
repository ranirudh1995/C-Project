#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
static int count;

/*Function that calcuates shortest path from source to target*/
double dijsktra(double cost[100][100],int source,int target,double array[20][2],char *path,int *no)
	{
	double dist[100],new_dist,minimum;
	int old[100],visited[100]={0};
	int i=0,j,k,m,beg=source,end=target;

	while(i < count)
		{
		dist[i] = INT_MAX;
		old[i] = -1;
		i++;
		}

	visited[beg]=1;
	dist[beg] = 0;

	while(visited[end]==0)
		{
		minimum = INT_MAX;
		m = 0;
		i=0;
		while(i< count)
			{
			new_dist = dist[beg] + cost[beg][i];
			if(visited[i]==0)
				{
				if(new_dist<dist[i])
					{
					dist[i] = new_dist;
					old[i] = beg;
					}
				if(minimum>dist[i])
					{
					minimum = dist[i];
					m = i;
					}
				}
			i++;
			}	
		beg = m;
		visited[beg] = 1;
		}

	beg = end;
	j = 0;

	while(beg != -1)
		{
		path[j++] = beg;
		beg = old[beg];
		}
    	*no=j;
	return dist[end];
	}
 
int main()
	{

	FILE *input,*initial,*output;
	char token[512],ch,path[100],path1[100];
	double array[20][2],dist[100][100];
	int i=0,j,a,b,beg,end;
	double total_dist,total_dist1,x,y;
   
     /*Copying the Nodes to an array*/

	input=fopen("graph.dat","r");
	fscanf(input,"%lf %lf",&x,&y);
	while(!feof(input))
		{
		array[i][0]=x;
		array[i][1]=y;
		i++;
		fgets(token,512,input);
		fscanf(input,"%lf %lf",&x,&y);
		}
	fclose(input);

	count=i;                 //Initialising Count
       
     /*Initialising all the elements to INFINITY (INT_MAX)*/

	for(a=0;a<count;a++)
		{
        	for(b=0;b<count;b++)
	        	{  
			dist[a][b]=INT_MAX;
	        	}	 
        	}

     /*Changing the given file into a 2-Dimensional Matrix containing the distances of each node with its adjacent nodes*/

	input=fopen("graph.dat","r");
	fgets(token,512,input);
    	for(i=0;i<count;i++)
        	{
		for(j=0;j<count;j++)
            		{
			fseek(input,-1*(strlen(token)),SEEK_CUR);
			ch=' ';
			while(ch!='\n')
				{
				fscanf(input,"%lf %lf",&x,&y);
				if(array[j][0]==x && array[j][1]==y)
					{
					dist[i][j]=sqrt((array[j][0]-array[i][0])*(array[j][0]-array[i][0])+(array[j][1]-array[i][1])*(array[j][1]-array[i][1]));
					}	
				fscanf(input,"%c",&ch);
                		}   	
			}
		fgets(token,512,input);
        	}	
	fclose(input);													}

        /*Calculating nearest node to Source and Target coordinates*/

	double initial_x,initial_y,final_x,final_y,min_initial,min_final,length_initial[100],length_final[100];
	double sort_i[100],sort_f[100];
	int node_initial[100],node_final[100];
	int beg_another,end_another,flag_i=0,flag_f=0,k,l;
	
	//Gettin Source and Target Coordinates

	initial = fopen("points.dat","r");

	fscanf(initial,"%lf %lf",&initial_x,&initial_y);
	fscanf(initial,"%lf %lf",&final_x,&final_y);

	fclose(initial);
	
	//Finding Shortest distance

    min_initial=sqrt((array[0][0]-initial_x)*(array[0][0]-initial_x)+(array[0][1]-initial_y)*(array[0][1]-initial_y));
    min_final=sqrt((array[0][0]-final_x)*(array[0][0]-final_x)+(array[0][1]-final_y)*(array[0][1]-final_y));

	for(i=0,j=0,l=0;i<count;i++)
		{
		length_initial[i]=sqrt((array[i][0]-initial_x)*(array[i][0]-initial_x)+(array[i][1]-initial_y)*(array[i][1]-initial_y));
		length_final[i]=sqrt((array[i][0]-final_x)*(array[i][0]-final_x)+(array[i][1]-final_y)*(array[i][1]-final_y));
		if(length_initial[i]<=min_initial)
			{
			min_initial=length_initial[i];
			sort_i[j]=length_initial[i];
			beg=i;
			node_initial[j]=i;
			j++;
			}
		if(length_final[i]<=min_final)
			{
			min_final=length_final[i];
			sort_f[l]=length_final[i];
			end=i;
			node_final[l]=i;
			l++;
			}
		}

        //Checking for any other node that is at equal distance from the source or target nodes other than the nearest one

	for(i=0;i<j-1;i++)
		{
		for(k=i+1;k<j;k++)
	 		{
	   		if(sort_i[i]==sort_i[k])
	   			{
	    			if(i!=beg)
	      				{
               				beg_another=node_initial[i];
	      				}
	   			flag_i=1;	 
        	   		}
         		}
       		}

	for(i=0;i<l-1;i++)
		{
         	for(k=i+1;k<l;k++)
         		{
            		if(sort_f[i]==sort_f[k])
	    			{
             			if(i!=end)
             				{
					end_another=node_final[i];
					}	
				flag_f=2;  
            			}
			}
       		}	

    /*Calculating and Printing Shortest Path*/   
        
    int no,no1;            //no & no1 represents no of nodes visited

    total_dist= dijsktra(dist,beg,end,array,path,&no); //Calling dijsktra function

    if(flag_i==1&&flag_f==2)
	{
        total_dist1= dijsktra(dist,beg_another,end_another,array,path1,&no1);
        }	

     else if(flag_i==1&&flag_f!=2)
     	{
        total_dist1= dijsktra(dist,beg_another,end,array,path1,&no1);
        }

    else if(flag_f==2&&flag_i!=1)
        {
        total_dist1= dijsktra(dist,beg,end_another,array,path1,&no1);
        }

    /*Creating a file in which the values can be stored*/
       
    output=fopen("path.dat","w");
    fprintf(output,"%0.3lf %0.3lf\n",initial_x,initial_y);
	
    if((final_x==array[path[0]][0]&&final_y==array[path[0]][1])&&(initial_x==array[path[no-1]][0]&&initial_y==array[path[no-1]][1]))
	 	{ 
        	while(no>=2)
            		{
            		fprintf(output,"%0.3lf %0.3lf\n",array[path[no-2]][0],array[path[no-2]][1]);
            		no--;
            		}
		}

	else if(initial_x==array[path[no-1]][0]&&initial_y==array[path[no-1]][1])
	 	{ 
        	while(no>=2)
            		{
            		fprintf(output,"%0.3lf %0.3lf\n",array[path[no-2]][0],array[path[no-2]][1]);
            		no--;
            		}
        	fprintf(output,"%0.3lf %0.3lf",final_x,final_y);
		}

	else if(final_x==array[path[0]][0]&&final_y==array[path[0]][1])
	 	{ 
        	while(no!=0)
            		{
            		fprintf(output,"%0.3lf %0.3lf\n",array[path[no-1]][0],array[path[no-1]][1]);
            		no--;
            		}
		}
	
	else
		{
	 	if(total_dist>total_dist1)
            		{
			while(no1!=0)
         			{
          			fprintf(output,"%0.3lf %0.3lf\n",array[path1[no1-1]][0],array[path1[no1-1]][1]);
          			no1--;
         			}
            		}
        	else
	    		{
            		while(no!=0)
                		{
                		fprintf(output,"%0.3lf %0.3lf\n",array[path[no-1]][0],array[path[no-1]][1]);
                		no--;
                		}
	    		}		
		
        	if(flag_i==0&&flag_f==0)
           		{
            		while(no!=0)
                		{
                		fprintf(output,"%0.3lf %0.3lf\n",array[path[no-1]][0],array[path[no-1]][1]);
                		no--;
                		}
			}
        	fprintf(output,"%0.3lf %0.3lf",final_x,final_y);
		}
     fclose(output);
     }
