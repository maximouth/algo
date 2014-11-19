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
  Voisin *voisin;
} Point;


typedef struct graph {
  int size;
  Point **Point;
} Graph;


#endif
