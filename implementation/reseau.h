# ifndef __RESEAU_H__
# define __RESEAU_H__

#include <stdio.h>

/* Liste chainee de noeuds */
typedef struct cellNoeud {
  struct noeud * cour ;  /* Pointeur vers le noeud courant */
  double poids;
  struct cellNoeud * suiv ;  /* Cellule suivante dans la liste */
} CellNoeud ;


/* Noeud du reseau */
typedef struct noeud {
  int num; /* Numero du noeud */
  int term; /* Noeud terminal ou non */
  int x , y ; /* Coordonnees du noeud*/
  CellNoeud * voisins ; /* Liste des voisins du noeud */
} Noeud ;

/* Un reseau */
typedef struct {
  int nbNoeuds ;       /* Nombre de noeuds du reseau */
  int nbAretes ;       /* Nombre maximal de fibres par cable */
  CellNoeud * noeuds ; /* Liste inverse des noeuds du reseau */
  Noeud *dep;          /* Premier noeud du reseau */
  CellNoeud *term ;    /* Liste des terminaux */ 
} Reseau ;

Noeud *creerNoeud();
CellNoeud *creerlistenoeud();
Reseau *creerReseau();
void detruireReseau(Reseau *res);
Noeud * recherche_nd(Reseau *res , int num);
Reseau *lectureReseau(FILE *f);
void ecrireReseauTxt(Reseau *res, FILE *f);
void ecrireReseauDot(Reseau *res, FILE *f);
void printReseau(Reseau *res);
void ajouteNoeudDansSuivant(Noeud *noeud1, Noeud *noeud2);

# endif

