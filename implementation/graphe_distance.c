#include "reseau.h"
#include "tas_dijkstra.h"
#include "dijkstra.h"


Reseau* grapheDistance(Reseau *res)
{
  Reseau *gd = NULL;
  CellNoeud *tmp1, *tmp2, *celltmp1, *celltmp2;
  CellNoeud *nc;
  Noeud *ndtmp1 = NULL;
  Noeud *ndtmp2 = NULL;
  Tas *tas;
  int nbNoeuds = 0;
  int nbAretes = 0;

  gd = creerReseau();

  tmp1 = res->term;
  while(tmp1 != NULL) {
    nc = creerlistenoeud();
    nc->cour = creerNoeud();

    if(gd->noeuds == NULL) {
      /* Premier noeud de la liste */
      gd->noeuds = nc;
      gd->dep = nc->cour;
    }
    else {
      /* Inserer un autre noeud */
      nc->suiv = gd->noeuds;
      gd->noeuds = nc;
    }

    ndtmp1 = nc->cour;

    /* Initialisation des champs du noeuds */
    ndtmp1->num = tmp1->cour->num;
    ndtmp1->term = 1;
    ndtmp1->x = tmp1->cour->x;
    ndtmp1->y = tmp1->cour->y;

    tmp1 = tmp1->suiv;
  }   
  
  tmp1 = gd->noeuds;
  while(tmp1 != NULL) {
    /* Initialiser le tas */
    tas = initTas(res);
    
    /* Appel de Dijkstra sur le noeud de départ */
    dijkstra(tas, res, tmp1->cour); 
    
    tmp2 = tmp1->suiv;
    while(tmp2 != NULL) {
      printf("GD : %d --> %d\n", tmp1->cour->num, tmp2->cour->num);

      //Chainage du voisin du noeud 1
      celltmp1 =creerlistenoeud();
      celltmp1->cour = tmp2->cour;
      celltmp1->poids = tas->val[tmp2->cour->num]->poids;
      celltmp1->suiv = tmp1->cour->voisins;
      tmp1->cour->voisins = celltmp1;
      
      //Chainage du voisin du noeud 2
      celltmp2 =creerlistenoeud();
      celltmp2->cour = tmp1->cour;
      celltmp2->poids = tas->val[tmp2->cour->num]->poids;
      celltmp2->suiv = tmp2->cour->voisins;
      tmp2->cour->voisins = celltmp2;

      nbAretes++;
      tmp2 = tmp2->suiv;
    }

    /* vider le tas, pour le prochan tour */
    detruireTas(tas);

    nbNoeuds++;
    tmp1 = tmp1->suiv;
  }

  gd->nbNoeuds = nbNoeuds;
  gd->nbAretes = nbAretes;
  
  return gd;
}

