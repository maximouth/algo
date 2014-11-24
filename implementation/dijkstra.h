#ifndef _DIS_h_
#define _DIS_h_

#include "tas_dijkstra.h"
#include "chaine.h"
#include "reseau.h"

Tas* initTas(Reseau *res);
void dijkstra(Tas *tas, Reseau *res, Noeud *deb);
void extraitTas(Tas *tas, Chaines *ch, Noeud *fin);
void initTab(int nbNoeuds);
void freeTab(int nbNoeuds);

#endif
