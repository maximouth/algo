#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// creer et initialiser une arete avec vide
Voisin *creerArete() {

  Voisin *new = NULL;
  new = malloc (sizeof (Voisin));

  new->point = NULL;
  new->cout = 0;
  new->suivant = NULL;

  printf("arrete crée\n");
  return new;
}


//creer et iitialiser un point à vide
Point *creerPoint() {

  Point *new= NULL;
  new = malloc (sizeof(Point));

  new->nom = NULL;
  new->term = true;
  new->x = 0;
  new->y = 0;

  new->voisin = NULL;
  new->suivant = NULL;

  printf("point terminal crée\n");
  return new;
}

// creer un graph de taille size
Graph *creerGraph(int nb_points, int nb_aretes) {
  Graph *new = NULL;
  new = malloc (sizeof (Graph));

  new->nb_points = nb_points;
  new->cout_max_arete = nb_aretes;
  new->points = NULL;

  printf("graphe créé\n");
  
return new;
}

// remplir les champs d'un point
void point(Point *p, char *nom, int x, int y, Point *suivant) {
  p->nom = strdup(nom);
  p-> x = x;
  p-> y = y;
  p->suivant = suivant;

  printf("point  avec %s\n", nom);
}


// retourne vrai si p appartient à g
boolean appartient (Graph *g, Point *p) {
  Point *pg = NULL;
  
  if(g == NULL) {
    printf("Graphe vide\n");
    exit(0);
  }

  pg = g->points;
  while(pg != NULL) {
    if( strcmp(pg->nom, p->nom) == 0) {
      printf("le point appartient a g\n");
      return true;
    }
    pg = pg->suivant;
  }

  printf("le point n'appartient pas a g\n");
  return false;
} 


//renvoie le point de g avec le nom // NULL si il n'existe pas de point
Point *retourne(Graph *g, char *nom) {
  Point *pg = NULL;
  
  if(g == NULL) {
    printf("Graphe vide\n");
    exit(0);
  }

  pg = g->points;
  while( pg != NULL ) {
    if( !strcmp(pg->nom, nom)) {
      return pg;
    }
    pg = pg->suivant;
  }

  return NULL;
}

// retourne -1 si p1 et p2 ne sont pas voisins
int CoutArete (Point *p1, Point *p2) {
  Voisin *a;

  if((p1 == NULL) || (p2 == NULL)) {
    printf("Points vide\n");
    exit(0);
  }
  
  a = p1->voisin;
  while (a != NULL) {
    if (! strcmp(a->point->nom, p2->nom)) {
      return a->cout;
    }
    a = a->suivant;
  }

  return -1;
}



//ajoute p à la fin de g
void ajouterPoint(Graph *g, Point *p) {

  if((g == NULL) || (p == NULL)) {
    printf("Parametre vide\n");
    exit(0);
  }

  if (appartient (g, p) == false) {
    p->suivant = g->points;
    g->points = p;
    printf("point '%s' ajouté\n", p->nom);
  }
  else {
    printf("le point appartient deja au graph\n");
  }
  
  return;
}

// Ajoute un voisin v au point p, et un voisin p au point v
void ajouterVoisin(Point *p1, Point *p2, int cout) {
  Voisin *v;
  
  /* Voisin de p1 -> p2 */
  v = creerArete();

  v->cout = cout;
  v->point = p2;

  v->suivant = p1->voisin;
  p1->voisin = v; 


  /* Voisin de p2 -> p1 */
  v = creerArete();

  v->cout = cout;
  v->point = p1;

  v->suivant = p2->voisin;
  p2->voisin = v;
}
