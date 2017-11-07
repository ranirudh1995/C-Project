/*
Authors: Rishabh Manoj, Anirudh Ravi, Penmetsa Murali Krishnam Raju, Samyak Upadhyay, Tadigadapa Abhiram and Nigel Steven Fernandez

Email IDs: Rishabh.Manoj@iiitb.org, Anirudh.Ravi@iiitb.org, raju.pmk@iiitb.org, Samyak.Upadhyay@iiitb.org, Abhiram.Tadigadapa@iiitb.org and NigelSteven.Fernandez@iiitb.org

Revision Number: 2

Date Modified: 22-12-2013
*/
#include "the_road_not_taken.h"

int main()
	{
	//get initial, final and obstacle point coordinates
	input();
	//compute the delaunay triangulation
	delaunay();
	//compute the voronoi graph
	voronoi();
	//compute the shortest path along the voronoi graph
	path();
	//display map 
	display();

	return 0;
	}
