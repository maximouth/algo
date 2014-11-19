#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// creer un arrete terminal
Voisin *creerArrete() {

  Voisin *new = NULL;
  new = malloc (sizeof (Voisin));

  new->nom = NULL;
  new->cout = 0;
  new->suiv = NULL;

  return new;
}


//creer un Point terminal
Point *creerPointTerm() {

  Point *new= NULL;
  new = malloc (sizeof(Point));

  new->nom = NULL;
  new->term = true;
  new->voisin = NULL;

  return new;
}

//creer un Point NON terminal
Point *creerPointNonTerm() {

  Point *new= NULL;
  new = malloc (sizeof(Point));

  new->nom = NULL;
  new->term = false;
  new->voisin = NULL;

  return new;
}



// creer un graph de taille size
Graph *creerGraph(int size) {
  int i = 0;
  Graph *new = NULL;
  new = malloc (sizeof (Graph));

  new->size = size;

  for (i = 0; i< size ; i++) {
    new->Point[i] = malloc (sizeof (Point));
    new->Point[i] = creerPointTerm();
  }

  return new;
}

/*
 * ////faire fonction init pour une point et une arrete///
 *
 */


//ajoute p à la fin de g
void ajouterPoint (Graph *g, Point *p) {
  g->Point[g->size] = malloc (sizeof(Point));
  g->Point[g->size] = p; 
}

// retourne vrai si p appartient à g
boolean appartient (Graph *g, Point *p) {
  int i = 0;

  for (i=0 ; i<g->size ; i++) {
    if( !strcmp(g->Point[i]->nom, p->nom)) {
      return true;
    }
  }
  return false;
} 


//renvoie le point de g avec le nom // NULL si il n'existe pas de point
Point *retourne(Graph *g, char *nom) {
 int i = 0;

  for (i=0 ; i<g->size ; i++) {
    if( !strcmp(g->Point[i]->nom, nom)) {
      return g->Point[i];
    }
  }
  return NULL;  

}

// retourne -1 si p1 et p2 ne sont pas voisins
int CoutArrete (Point *p1, Point *p2) {
 
  Voisin *a = p1->voisin;
  while (a) {
    if (! strcmp(a->nom, p2->nom)) {
      return a->cout;
    }
    a = a->suiv;
  }

  return -1;
}
