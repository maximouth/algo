#include <stdio.h>
#include <stdlib.h>
#include <float.h>


#include "tas_dijkstra.h"
#include "dijkstra.h"
#include "reseau.h"
#include "prim.h"


void ajouterNoeud(Reseau *st, int i)
{
  Noeud *n = NULL;

  n = recherche_nd(st , i);
  if( n == NULL ) {
    /* creer le noeud, l'initialiser et l'ajouter */
  } 
}

void ajoutSteiner(Reseau *st, Tas *tas, int deb, int arr) 
{
  /* rechercher le noeud deb dans st, si noeud n'existe pas, l'ajouter */
  ajouterNoeud(st, deb);

  /* rechercher le noeud arr dans st, si noeud n'existe pas, l'ajouter */
  ajouterNoeud(st, arr);

  /* Pour tous les noeuds n de arr vers deb */
  /* Rechercher le noeud n dans st, si Noeud n'existe pas l'ajouter */
  
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
      
      /* Calcul de Dijkstra à partir du noeud i */
      dijkstra(tas, res, nPred);

      /* Ajout des noeuds du chemin pred[i] -> i*/
      ajoutSteiner(st, tas, i, prim->pred[i]);
    }
  }
  
  return st;
}
