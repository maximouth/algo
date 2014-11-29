#ifndef _Tas_Disjkstra_h_
#define _Tas_Disjkstra_h_

#include "reseau.h"

// structure element
typedef struct elem {
  int numero;
  int precedent;
  double poids;
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



Tas *initialiser(int taille);
int est_vide(Tas *t);
void ajouter(Tas *t, Elem *el);
void supprime(Tas *t, int idx);
Elem *recup_min(Tas *t);

Tas* initTas(Reseau *res);

Elem *creerElem();
void remplirElem(Elem *el, Noeud *n, int precedent, double poids);

void miseAJour(Tas *t, Elem *el);
Elem *rechercher(Tas *t, int idx);
void afficher(Tas* t);

#endif
