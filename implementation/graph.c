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

  printf("arrete crée\n");
  return new;
}


//creer un Point terminal
Point *creerPointTerm() {

  Point *new= NULL;
  new = malloc (sizeof(Point));

  new->nom = NULL;
  new->term = true;
  new->voisin = NULL;
  printf("point terminal crée\n");
  return new;
}

//creer un Point NON terminal
Point *creerPointNonTerm() {

  Point *new= NULL;
  new = malloc (sizeof(Point));

  new->nom = NULL;
  new->term = false;
  new->voisin = NULL;

    printf("point non terminal crée\n");
  return new;
}



// creer un graph de taille size
Graph *creerGraph(int size) {
  int i = 0;
  Graph *new = NULL;
  new = malloc (sizeof (Graph));

  new->max = size;
  new->size = 0;

  for (i = 0; i< size ; i++) {
    printf("boucle graph n%d\n",i);
    new->Point[i] = malloc (sizeof (Point));
    printf("malloc reussi\n");
    //new->Point[i] = creerPointTerm();
    // printf("point crée\n");
  }

    printf("graph crée\n");
  return new;
}

//initialise le champ nom d'un point
void initPoint(Point *p, char *nom) {
  p->nom = strdup(nom);
  printf("point initialisé avec %s\n", nom);
}


//initialise le champs nom et cout d'un voisin
void initVoisin(Voisin *v, char *nom, int cout) {
  v->nom = strdup(nom);
  v->cout = cout;
  printf("voisin initialisé avec %s\n", nom);
}

    

// retourne vrai si p appartient à g
boolean appartient (Graph *g, Point *p) {
  int i = 0;
  if (g->size == 0) {
    return false;
  }

  for (i=0 ; i<g->size ; i++) {
    if( !strcmp(g->Point[i]->nom, p->nom)) {
      printf("le point appartient a g\n");
      return true;
    }
  }
  printf("le point n'appartient pas a g\n");
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



//ajoute p à la fin de g
void ajouterPoint (Graph *g, Point *p) {
  
  if (g->size >= g->max) {
    printf("graph plein \n");
    return;
  }

  if (appartient (g, p) == false) {
    //g->Point[g->size] = malloc (sizeof(Point));
    g->Point[g->size] = p;
    printf("point '%s' ajouté\n", p->nom);
  }
  else {
    printf("le point appartient deja au graph\n");
    return;
  }
  g->size++;
}

//ajoute un voisin v au point p, et un voisin p a v
void ajouterVoisin(Graph *g , Voisin *v, Point *p) {
  
  Point *deux = NULL;
  Voisin *tmp = creerArrete();
  initVoisin (tmp, p->nom, v->cout);

  v->suiv = p->voisin;
  p->voisin = v;

  deux = retourne(g, v->nom);
  tmp->suiv = deux->voisin;
  deux->voisin = tmp;
}
