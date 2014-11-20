#include "entree_sortie.h"
#include "graph.h"
#include "lectGraph.h"


#include <string.h>


/*
 *  ouvrir fichier, lire le nb de point quil y a et initialiser un graph avec
 *  ( = nb de lignes a lire correspondants au points )
 *  lire les lignes correspondant au points et creer un point correspondant
 *  a celle ci, et les integrer au graph
 *
 *  lire jusqu'a la fin (sauf si nb de voisin)  
 *  creer un voisin correspondant a la ligne et l'ajouter comme voisin
 *
 */

Graph *lectGraph(FILE *f) {

  Graph *g = NULL;
  int taille = 10;
  char s [taille];
  int nbPoint;
  int nbArrete;
  Point *p = NULL;
  int cpt = 0;
  int tmp;
  Voisin *v = NULL;
  char *temp = NULL;

  //lire le nombre de points
  GetChaine(f, taille, s);
  printf("nb de point : %s\n",s);
  nbPoint = atoi(s);
  
  // lire le nombre d'arrete
  GetChaine(f, taille, s);
  printf("nb d'arrretes : %s\n",s);
  nbArrete = atoi(s);
  
  //creation d'un graph de nbPoint points
  g = creerGraph(nbPoint);
  
  //tant qu'il y a des points a lire faire :
  while (cpt < nbPoint) {
    
    p = creerPointTerm();

    //lire le nom du point
    GetChaine(f, taille, s);
    printf("nom du point : %s ",s);
    p->nom = strdup (s);

    //savoir si point terminal ou pas
    GetChaine(f, taille, s);
    printf("terminal? : %s ",s);
    tmp = atoi(s);
    
    if (tmp == 0) {
     p->term = false;
    }
    
    // recuperer les coordonées
    GetChaine(f, taille, s);
    printf("(%s,",s);
    tmp = atoi(s);
    
    p->x = tmp;

    GetChaine(f, taille, s);
    printf("%s)\n",s);
    tmp = atoi(s);
    p->y = tmp;

    ajouterPoint(g,p);
    cpt++;
  }

  // maintenant lire les voisins et les ajouter

  cpt = 0;
  while (cpt < nbArrete) {
    v = creerArrete();
    
    //nom du premier point
    GetChaine(f, taille, s);
    printf("arrete en %s et",s);
    p = retourne (g , s);

    //nom du 2eme point
    GetChaine(f, taille, s);
    printf(" %s",s);
    temp = strdup(s);

    //cout de l'arrete
    GetChaine(f, taille, s);
    printf("et de cout :%s\n",s);
    tmp = atoi(s);

    initVoisin(v ,temp, tmp);  

    ajouterVoisin(g, v, p);

    cpt++;
  }

  return g;
}
