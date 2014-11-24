#ifndef _Tas_Disjkstra_h_
#define _Tas_Disjkstra_h_

#include "reseau.h"

// structure element
typedef struct elem {
  int numero;
  int precedent;
  double distance;
  Noeud *noeud;
  int posTas;
} Elem;


// structure de tas
typedef struct tas {
  Elem **val;
  int *tas;
  int nbNoeud;
  int nbMax;
} Tas;



Elem *creerElem();
Tas *creerTas(int taille);
void remplirElem(Elem *el, Noeud *n, int precedent, double dist);

void inserer(Tas *t, Elem *el);
void supprimer(Tas *t, int idx);
void miseAJour(Tas *t, Elem *el);
Elem *rechercher(Tas *t, int idx);
int tasVide(Tas *t);
Elem *minimum(Tas *t);
void afficher(Tas* t);

#endif
