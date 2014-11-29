
GCC=gcc
GPP=g++

#FLAGS=-Wall -g -D DEBUG
FLAGS=-Wall -g 
GCCFLAGS=  -g
CPPFLAGS= -D DEBUG
LIBS= -lm

# User definitions must be here
EXEC = Projet_ex.x
INCS = reseau.h \
entree_sortie.h \
tas_dijkstra.h \
dijkstra.h \
prim.h \
graphe_distance.h 

SOURCES = reseau.c \
entree_sortie.c \
tas_dijkstra.c \
dijkstra.c \
prim.c \
graphe_distance.h \
main.c  

OBJS = $(SOURCES:.c=.o)


# Building the world
all: $(EXEC) 

$(EXEC): $(INCS) $(OBJS) 
	$(GCC) $(GCCFLAGS) $(OBJS) $(LIBS) -o $(EXEC) 


.SUFFIXES:
.SUFFIXES: .c .cc .o

.cc.o:
	$(GPP) $(FLAGS) -c $<

.c.o:
	$(GCC) $(FLAGS) -c $<


# Clean up
clean:
	rm -f *~ .*~ \#*\# *.o *.tmp* Chaine*.txt *.png *.plt Reseau*.txt
	rm -f $(EXEC) 

# Dependencies
depend: 

	$(GCC) -M $(CPPFLAGS) $(SOURCES) > .depend
include .depend



