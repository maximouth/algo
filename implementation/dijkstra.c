#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "chaine.h"
#include "entree_sortie.h"
#include "fplot.h"
#include "reseau.h"
#include "arbre.h"
#include "reseau.h"
#include "hachage.h"
#include "dijkstra.h"

int **tab;

/* double calcDistance(Noeud *a, Noeud *b) */
/* { */
/*   double dist; */

/*   dist = sqrt ( (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y)); */

/*   return(dist); */
/* } */

double calcDistance(Noeud *a, Noeud *b)
{
  double dist;

  dist = sqrt ( (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));

  if(a->num < b->num)
    return(((tab[a->num][b->num]+1)^2)*dist);
  else
    return(((tab[b->num][a->num]+1)^2)*dist);
}

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
    remplirElem(e, n->cour, -1, FLT_MAX);
    inserer(t, e);
    n = n->suiv;
  }

  return t;
}


void dijkstra(Tas *tas, Reseau *res, Noeud *deb) {

  Elem *e;
  CellNoeud *voisin;
  double distance;

  //mettre le noeud de départ à la racine du tas
  tas->val[deb->num]->distance = 0.0;
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
      distance = calcDistance(e->noeud, voisin->cour);

      if(e->distance+distance < tas->val[voisin->cour->num]->distance) {
	tas->val[voisin->cour->num]->distance = e->distance+distance;
	tas->val[voisin->cour->num]->precedent = e->numero;
	miseAJour(tas, tas->val[voisin->cour->num]);
	if(e->noeud->num < voisin->cour->num) {
	  tab[e->noeud->num][voisin->cour->num]++;
	}
	else {
	  tab[voisin->cour->num][e->noeud->num]++;
	}
      }
      //traiter le voisin suivant
      voisin = voisin->suiv;
    }
  }
}


void extraitTas(Tas *tas, Chaines *ch, Noeud *fin)
{
  Elem *e = tas->val[fin->num];
  CellChaine *cell;
  CellPoint *p;

  //creation de la nouvelle chaine
  cell = creerCellchaine();
  cell->numero = ch->nbChaines;
  
  while(e->precedent != -1) {
    p = creerPoint();
    p->suiv = cell->points;
    cell->points = p;
    p->x = e->noeud->x;
    p->y = e->noeud->y;
    
    // trouver le noeud précédent
    e = tas->val[e->precedent];
  }
  
  // inserer le premier noeud
  p = creerPoint();
  p->suiv = cell->points;
  cell->points = p;
  p->x = e->noeud->x;
  p->y = e->noeud->y;
  
  //chainer la chaine à la liste des chaines
  cell->suiv = ch->chaines;
  ch->chaines = cell;

  //incrementer le nombre de chaine
  ch->nbChaines++;
}
