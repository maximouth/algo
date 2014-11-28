#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "entree_sortie.h"
#include "reseau.h"
#include "dijkstra.h"


/* double calcDistance(Noeud *a, Noeud *b) */
/* { */
/*   double dist; */

/*   dist = sqrt ( (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y)); */

/*   return(dist); */
/* } */

double calcDistance(Noeud *a, CellNoeud *b)
{
  return b->poids;
}

/*
void initTab(int nbNoeuds)
{
  int i;
  
  tab = (int * *) malloc( nbNoeuds * sizeof( int *));
  for(i = 0; i<nbNoeuds; i++) {
    tab[i] = (int *) malloc( nbNoeuds * sizeof(int));
  }
}

void freeTab(int nbNoeuds) 
{
  int i;

  for(i = 0; i<nbNoeuds; i++) {
    free(tab[i]);
  }
  free(tab);
}
*/

Tas *initTas(Reseau *res) 
{
  Tas *t;
  CellNoeud *n = NULL;
  Elem *e;

  //creer un tas de la taille du reseau
  t = creerTas(res->nbNoeuds);
  
  //inserer tous les noeuds du reseau avec une distance max
  n = res->noeuds;

  while(n != NULL) {
    e = creerElem();
    remplirElem(e, n->cour, -1, INT_MAX);
    inserer(t, e);
    n = n->suiv;
  }

  return t;
}


void dijkstra(Tas *tas, Reseau *res, Noeud *deb) {

  Elem *e;
  CellNoeud *voisin;
  double poids;

  //mettre le noeud de départ à la racine du tas
  tas->val[deb->num]->poids = 0.0;
  miseAJour(tas, tas->val[deb->num]);
  
  while(!tasVide(tas)) {
    //rechercher le plus petit noeud non parcouru 
    e = minimum(tas);

    //marquer le noeud en le supprimant du tas
    supprimer(tas, e->numero);
    
    // parcourir tous les voisins du noeud
    voisin = e->noeud->voisins;
    while(voisin != NULL) {
      //calcul de la distance entre le noeud et son voisin
      poids = calcDistance(e->noeud, voisin);

      if(e->poids+poids < tas->val[voisin->cour->num]->poids) {
	tas->val[voisin->cour->num]->poids = e->poids+poids;
	tas->val[voisin->cour->num]->precedent = e->numero;
	miseAJour(tas, tas->val[voisin->cour->num]);
      }
      //traiter le voisin suivant
      voisin = voisin->suiv;
    }
  }
}


void afficheDij(Tas *tas, Reseau *res, FILE *f) {

  int i = 0;
  CellNoeud *noeuds = NULL;  
 
  
  if(res == NULL) {
    printf("EcrireReseauTxt : Erreur réseau vide\n");
    return;
  }
    
  if(f == NULL) {
    printf("EcrireReseauTxt : Fichier de sortie non ouvert.\n");
    return;
  }

  /* Entete du fichier */
  fprintf(f,"digraph g { \n\trankdir = LR\n\tbgcolor = grey50\n\tsize = \"1500\"\n\n");
  
 /* Ecriture des coordonnées des noeuds */
  noeuds = res->noeuds; 
  while(noeuds != NULL) {
    fprintf(f,"\tmyNode%d [\n", noeuds->cour->num);
    fprintf(f,"\tlabel = \"%d\"\n", noeuds->cour->num);
    if(noeuds->cour->term == 1)
      fprintf(f,"\tcolor = blue\n");
    else
      fprintf(f,"\tcolor = green\n");      
    fprintf(f,"\tpos = \"%d,%d\"\n",noeuds->cour->x, noeuds->cour->y);
    fprintf(f,"\t]\n\n");
    
    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }
  fprintf(f, "\n"); 


 for(i = 0; i<res->nbNoeuds-1; i++) {
     	fprintf(f,"\"myNode%d\" -> \"myNode%d\" [ \tpenwidth = 0.001 \n\t color = red\n\tlabel = \"%f\" ]\n",tas->val[i]->numero, tas->val[i]->precedent, tas->val[i]->poids );
    }

 fprintf(f,"\n}\n");
}


