
#include <string.h>

#include "entree_sortie.h"
#include "reseau.h"
#include "lectGraph.h"

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

Reseau *lectGraph(FILE *f) {

  Reseau *res = NULL;
  int taille = 10;
  char s [taille];
  int nbPoints;
  int nbAretes;
  Point *p = NULL;
  Point *p2 = NULL;
  int cpt = 0;
  int tmp;

  //lire le nombre de points
  GetChaine(f, taille, s);
  printf("nb de point : %s\n",s);
  nbPoints = atoi(s);
  
  // lire le nombre d'arete
  GetChaine(f, taille, s);
  printf("nb d'arrretes : %s\n",s);
  nbAretes = atoi(s);
  
  //creation d'un graph de nbPoint points
  res = creerReseau(nbPoints, nbAretes);
  
  //tant qu'il y a des points a lire faire :
  for(cpt = 0; cpt < nbPoints; cpt++) {    
    p = creerNoeud();

    //lire le nom du point
    GetChaine(f, taille, s);
    printf("nom du point : %s ",s);
    p->num = atoi(s);

    //savoir si point terminal ou pas
    GetChaine(f, taille, s);
    printf("terminal? : %s ",s);
    tmp = atoi(s);
    
    if (tmp == 0) {
      p->term = false;
    }
    else {
     p->term = true;
    }
    
    // recuperer les coordonnees
    GetChaine(f, taille, s);
    printf("(%s,",s);
    p->x = atoi(s);

    GetChaine(f, taille, s);
    printf("%s)\n",s);
    p->y = atoi(s);

    ajouterPoint(g,p);
  }

  // maintenant lire les voisins et les ajouter
  for(cpt = 0; cpt < nbAretes; cpt++) {

    //nom du premier point
    GetChaine(f, taille, s);
    printf("arete en %s et",s);
    p = retourne (g, s);

    //nom du 2eme point
    GetChaine(f, taille, s);
    printf("arete en %s et",s);
    p2 = retourne (g, s);

    //cout de l'arete
    GetChaine(f, taille, s);
    printf("et de cout :%s\n",s);
    tmp = atoi(s);

    ajouterVoisin(p, p2, tmp);
  }

  return g;
}
