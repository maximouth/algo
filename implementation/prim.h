#ifndef _PRIM_h_
#define _PRIM_h_

#include <float.h>

#include "tas_dijkstra.h"
#include "reseau.h"

 /* Noeud du reseau */
typedef struct prim {
  int *pred; /* Tableau des predecesseurs */
  double *d; /* Tableau des distances */
} Prim ;



/* Algorithme de Prim */
Prim* prim(Tas *tas, Reseau *res, Noeud *deb);

/* Calcul le poids d'un arbre englobant */
double calculPoids(Prim *prim, Reseau *res);

/* Affichage de l'arbre de Prim en dot */
void affichePrim(Prim *prim, Reseau *res, FILE *f);

#endif
