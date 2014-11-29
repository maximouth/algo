#ifndef _DIS_h_
#define _DIS_h_

#include "tas_dijkstra.h"
#include "reseau.h"

/* Algorithme de Dijkstra */
void dijkstra(Tas *tas, Reseau *res, Noeud *deb);

/* Affichage de l'arbre de Dijkstra en dot */
void afficheDij(Tas *t, Reseau *res, FILE *f);

#endif
