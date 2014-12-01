#include <stdio.h>
#include <stdlib.h>
#include <float.h>


#include "tas_dijkstra.h"
#include "dijkstra.h"
#include "reseau.h"
#include "prim.h"

float trouvePoids(Noeud *n1, Noeud *n2)
{
  CellNoeud *n = n1->voisins;

  while(n != NULL) {
    if(n2->num == n->cour->num)
      return n->poids;
    n = n->suiv;
  }
  return 0.0;
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
  Noeud *n, *nPrec;
  int i;
  float p;
  CellNoeud *celltmp1 = NULL;
  CellNoeud *celltmp2 = NULL;

  /* rechercher le noeud arr dans st, si noeud n'existe pas, l'ajouter */
  n = ajouterNoeud(st, tas, arr);

  /* rechercher le noeud deb dans st, si noeud n'existe pas, l'ajouter */
  n = ajouterNoeud(st, tas, deb);

  printf("Ajout Steiner : %d %d.\n", deb, arr);

  /* Pour tous les noeuds n de arr vers deb */
  i = deb;

  /* Rechercher le noeud n dans st, si Noeud n'existe pas l'ajouter */
  while( tas->val[i]->precedent != -1 ) {
    printf("Ajout steiner : %d(%d) -> %d\n", tas->val[i]->noeud->num, tas->val[i]->precedent, i);
    /* rechercher le noeud deb dans st, si noeud n'existe pas, l'ajouter */
    nPrec = ajouterNoeud(st, tas, tas->val[i]->precedent);

    p = trouvePoids(tas->val[i]->noeud, tas->val[tas->val[i]->precedent]->noeud);

    //Chainage du voisin du noeud 1
    celltmp1 =creerlistenoeud();
    celltmp1->cour = n;
    celltmp1->suiv = nPrec->voisins;
    nPrec->voisins = celltmp1;
    celltmp1->poids = p;
    
    //Chainage du voisin du noeud 2
    celltmp2 =creerlistenoeud();
    celltmp2->cour = nPrec;
    celltmp2->suiv = n->voisins;
    n->voisins = celltmp2;
    celltmp2->poids = p;

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
  
  for(i = 0; i <prim->nbNoeuds; i++) {
    if(prim->pred[i] != -1 ) {
      /* Recherche des noeuds d'indice pred[i] dans le reseau res */
      nPred = recherche_nd(res, prim->pred[i]);
      
      /* Initialisation du Tas a partir du reseau res */
      detruireTas(tas);
      tas = initTas(res);
      printf("AV : tas->NbMax : %d, tas->nbNoeud : %d\n", tas->nbMax, tas->nbNoeud);
      
      /* Calcul de Dijkstra à partir du noeud i */
      dijkstra(tas, res, nPred);

      printf("nPred : %d, nbNoeud : %d\n", nPred->num, res->nbNoeuds);
      printf("AP : tas->NbMax : %d, tas->nbNoeud : %d\n", tas->nbMax, tas->nbNoeud);

      /* Ajout des noeuds du chemin pred[i] -> i*/
      ajoutSteiner(st, tas, i, prim->pred[i]);
    }
  }
  
  return st;
}
