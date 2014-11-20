#ifndef _GRAPH_H
#define _GRAPH_H

typedef enum {true, false} boolean;


typedef struct voisin {
  char *nom;
  int cout;
  struct voisin *suiv;
} Voisin;


typedef struct point {
  boolean term;
  char *nom;
  int x;
  int y;
  Voisin *voisin;
} Point;


typedef struct graph {
  int max;
  int size;
  Point *Point[];
} Graph;


Voisin *creerArrete();
Point *creerPointTerm();
Point *creerPointNonTerm();
Graph *creerGraph(int size);



void initPoint(Point *p, char *nom, int x, int y);
void initVoisin(Voisin *v, char *nom, int cout);

boolean appartient (Graph *g, Point *p);
Point *retourne(Graph *g, char *nom);
int CoutArrete (Point *p1, Point *p2);

void ajouterPoint (Graph *g, Point *p);
void ajouterVoisin(Graph *g , Voisin *v, Point *p);


#endif
