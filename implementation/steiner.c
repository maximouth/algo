#include <stdio.h>
#include <stdlib.h>
#include <float.h>


#include "tas_dijkstra.h"
#include "dijkstra.h"
#include "reseau.h"
#include "prim.h"

double trouvePoids(Noeud *n1, Noeud *n2)
{
  CellNoeud *n = n1->voisins;

  while(n != NULL) {
    if(n2->num == n->cour->num)
      return n->poids;
    n = n->suiv;
  }
  return 0.0;
}

void ajoutVoisin(Noeud *nDeb, Noeud *nArr, double p)
{
  CellNoeud *n = nDeb->voisins;
  CellNoeud *celltmp;
  int trouve = 0;

  while(n != NULL && !trouve) {
    if(n->cour->num == nArr->num) 
      trouve = 1;
    n = n->suiv;
  }

  if(!trouve) {
    /* Le noeud n'existe pas dans la liste des voisins */
    /* Chainage du voisin du noeud 1*/
    celltmp =creerlistenoeud();
    celltmp->cour = nArr;
    celltmp->suiv = nDeb->voisins;
    nDeb->voisins = celltmp;
    celltmp->poids = p;
  }
}

/* Ajouter un noeud dans le réseau si il n'existe pas, */
/* Retourne le noeud */
Noeud* ajouterNoeud(Reseau *res, Tas *tas, int i)
{
  Noeud *n = NULL;
  CellNoeud * noeuds = NULL;

  n = recherche_nd(res , i);
  if( n == NULL ) {
    /* creer le noeud, l'initialiser et l'ajouter */
    n = creerNoeud();
    n->num = tas->val[i]->noeud->num;
    n->x = tas->val[i]->noeud->x;
    n->y = tas->val[i]->noeud->y;
    n->term = tas->val[i]->noeud->term;

    /* creer la cellule de noeud */
    noeuds = creerlistenoeud();
    noeuds->cour = n;
    /* CHainer le nouveau noeud */
    if(res->noeuds == NULL) {
      /* Premier noeud de la liste */
      res->noeuds = noeuds;
      res->dep = noeuds->cour;
    }
    else {
      /* Inserer un autre noeud */
      noeuds->suiv = res->noeuds;
      res->noeuds = noeuds;
    }
  }

  return n;
}

void ajoutSteiner(Reseau *st, Tas *tas, int deb, int arr) 
{
  Noeud *nDeb, *nArr, *nPrec;
  int i;
  double p;

  /* rechercher le noeud arr dans st, si noeud n'existe pas, l'ajouter */
  nArr = ajouterNoeud(st, tas, arr);

  /* rechercher le noeud deb dans st, si noeud n'existe pas, l'ajouter */
  nDeb = ajouterNoeud(st, tas, deb);

#ifdef DEBUG
  printf("Ajout Steiner : %d -> %d.\n", deb, arr);
#endif

  /* Pour tous les noeuds n de arr vers deb */
  i = deb;

  /* Rechercher le noeud n dans st, si Noeud n'existe pas l'ajouter */
  while( i != -1 ) {
#ifdef DEBUG
    printf("Ajout steiner : %d(%d) -> %d\n", tas->val[i]->noeud->num, tas->val[i]->precedent, i);
#endif

    if(tas->val[i]->precedent != -1) {
      /* rechercher le noeud deb dans st, si noeud n'existe pas, l'ajouter */
      nPrec = ajouterNoeud(st, tas, tas->val[i]->precedent);
      p = trouvePoids(tas->val[i]->noeud, tas->val[tas->val[i]->precedent]->noeud);
    }      
    else {
      /* C'est le dernier noeud */
      nPrec = nArr;
      p = trouvePoids(tas->val[i]->noeud, nArr);
    }

    ajoutVoisin(nDeb,nPrec, p);
    ajoutVoisin(nPrec,nDeb, p);

    nDeb = nPrec;
    i = tas->val[i]->precedent;
  }
}

Reseau* steiner(Prim *prim, Reseau *res)
{
  Reseau *st = NULL;
  int i;
  Noeud *nPred = NULL;
  Tas *tas = NULL;

  st = creerReseau();
  st->nbNoeuds = res->nbNoeuds;
  st->dep = res->dep;
  
  for(i = 0; i <prim->nbNoeuds; i++) {
    if(prim->pred[i] != -1 ) {
      /* Recherche des noeuds d'indice pred[i] dans le reseau res */
      nPred = recherche_nd(res, prim->pred[i]);
      
      /* Initialisation du Tas a partir du reseau res */
      detruireTas(tas);
      tas = initTas(res);
#ifdef DEBUG
      printf("AV : tas->NbMax : %d, tas->nbNoeud : %d\n", tas->nbMax, tas->nbNoeud);
#endif
      
      /* Calcul de Dijkstra à partir du noeud i */
      dijkstra(tas, res, nPred);

      /* Ajout des noeuds du chemin pred[i] -> i*/
      ajoutSteiner(st, tas, i, prim->pred[i]);
    }
  }
  
  return st;
}
