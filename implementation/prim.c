#include <stdio.h>
#include <stdlib.h>
#include <float.h>


#include "tas_dijkstra.h"
#include "reseau.h"
#include "prim.h"

/* Algorithme de Prim */
Prim* prim(Tas *tas, Reseau *res, Noeud *deb)
{
  int *pred=NULL;
  double *d=NULL;
  int *M=NULL;
  Elem *e;
  CellNoeud *voisin;
  int i;
  Prim *prim;

  prim = malloc(sizeof(Prim));
  pred = malloc(res->nbNoeuds*sizeof(int));
  d = malloc(res->nbNoeuds*sizeof(double));
  M = malloc(res->nbNoeuds*sizeof(int));

  prim->nbNoeuds = res->nbNoeuds;

  for(i = 0; i < res->nbNoeuds; i++) {
    pred[i] = -1;
    d[i] = FLT_MAX;
    M[i] = 0;
  }

  //mettre le noeud de départ à la racine du tas
  tas->val[deb->num]->poids = 0.0;
  miseAJour(tas, tas->val[deb->num]);

  d[deb->num] = 0.0;
  M[deb->num] = 1;

  while(!est_vide(tas)) {
    //rechercher le plus petit noeud non parcouru 
    e = recup_min(tas);
    
    // parcourir tous les voisins du noeud
    voisin = e->noeud->voisins;
    while(voisin != NULL) {
      if(M[voisin->cour->num] == 0) {
	d[voisin->cour->num] = voisin->poids;
	pred[voisin->cour->num] = e->noeud->num;
	tas->val[voisin->cour->num]->poids = voisin->poids;
	miseAJour(tas, tas->val[voisin->cour->num]);
	M[voisin->cour->num] = 1;
      }
      else {
	if((M[voisin->cour->num] != 2) && 
	   (d[voisin->cour->num] > voisin->poids )) {
	  d[voisin->cour->num] = voisin->poids;
	  pred[voisin->cour->num] = e->noeud->num;
	  tas->val[voisin->cour->num]->poids = voisin->poids;
	  miseAJour(tas, tas->val[voisin->cour->num]);	  
	}
      }

      //traiter le voisin suivant
      voisin = voisin->suiv;
    }
    M[e->noeud->num] = 2;
  }

  prim->pred = pred;
  prim->d = d;

  return prim;
}

double calculPoids(Prim *prim, Reseau *res)
{
  int i;
  double p;

  for(i = 0; i< res->nbNoeuds; i++) {
    if(prim->pred[i] != -1) {
      p = p + prim->d[i];
    }
  }

  return p;
}

void affichePrim(Prim *prim, Reseau *res, FILE *f) {
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
  fprintf(f,"graph g { \n\trankdir = LR\n\tbgcolor = grey50\n\tsize = \"1500\"\n\n");
  
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

  for(i = 0; i< res->nbNoeuds; i++) {
    if(prim->pred[i] != -1) {
      fprintf(f,"\"myNode%d\" -- \"myNode%d\" [ \tpenwidth = 0.001 \n\t color = red\n\tlabel = \"%f\" ]\n", i, prim->pred[i], prim->d[i]);
    }
  }
  
 fprintf(f,"\n}\n");
}
