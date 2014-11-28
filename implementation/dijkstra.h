#ifndef _DIS_h_
#define _DIS_h_

#include <stdio.h>

#include "tas_dijkstra.h"
#include "reseau.h"

Tas* initTas(Reseau *res);
void dijkstra(Tas *tas, Reseau *res, Noeud *deb);
void initTab(int nbNoeuds);
void freeTab(int nbNoeuds);
void afficheDij(Tas *t, Reseau *res, FILE *f);

#endif
