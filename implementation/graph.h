#ifndef _GRAPH_H
#define _GRAPH_H

typedef enum {false, true} boolean;

typedef struct point {
  boolean term;
  char *nom;
  int x;
  int y;
  struct voisin *voisin;
  struct point *suivant;
} Point;

typedef struct voisin {
  Point *point;
  int cout;
  struct voisin *suivant;
} Voisin;

typedef struct graph {
  int nb_points;
  int cout_max_arete;
  Point *points;
} Graph;


Voisin *creerArete();
Point *creerPoint();
Graph *creerGraph(int nb_points, int nb_aretes);

void initPoint(Point *p, char *nom, int x, int y);

boolean appartient (Graph *g, Point *p);
Point *retourne(Graph *g, char *nom);
int CoutArete (Point *p1, Point *p2);

void ajouterPoint (Graph *g, Point *p);
void ajouterVoisin(Point *p1, Point *p2, int cout);


#endif
