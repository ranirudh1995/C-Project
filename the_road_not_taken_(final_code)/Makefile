#Authors: Rishabh Manoj, Anirudh Ravi, Penmetsa Murali Krishnam Raju, Samyak Upadhyay, Tadigadapa Abhiram and Nigel Steven Fernandez
#
#Email IDs: Rishabh.Manoj@iiitb.org, Anirudh.Ravi@iiitb.org, raju.pmk@iiitb.org, Samyak.Upadhyay@iiitb.org, Abhiram.Tadigadapa@iiitb.org and NigelSteven.Fernandez@iiitb.org
#
#Revision Number: 3
#
#Date Modified: 22-12-2013
#
VPATH = by_Steven_Fortune 
_OBJ = delaunay.o edgelist.o geometry.o heap.o fortune.o memory.o output.o the_road_not_taken.o input.o voronoi.o path.o display.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
DEPS = defs.h headers.h the_road_not_taken.h
ODIR = object_files
LIBS = -lm -lgraph -lX11

the_road_not_taken : $(OBJ) $(DEPS)
	gcc $(OBJ) $(LIBS) -o $@

$(ODIR)/%.o : %.c $(DEPS)
	gcc $< $(LIBS) -c -o $@
	
.PHONY : clean
clean :
	rm -f -r the_road_not_taken points.dat obstacles.dat graph.dat delaunay.dat path.dat $(ODIR)/*.o
