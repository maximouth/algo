# ifndef __RESEAU_H__
# define __RESEAU_H__

#include <stdio.h>

/* Liste chainee de noeuds */
typedef struct cellNoeud {
  struct noeud * cour ;  /* Pointeur vers le noeud courant */
  int poids;
  struct cellNoeud * suiv ;  /* Cellule suivante dans la liste */
} CellNoeud ;


 /* Liste chainee de commodites */
typedef struct cellCommodite {
  struct noeud * extrA , * extrB ; /* Noeuds aux extremites de la commodite */
  struct cellCommodite * suiv ;  /* Cellule suivante dans la liste */
} CellCommodite ;


 /* Noeud du reseau */
typedef struct noeud {
  int num; /* Numero du noeud */
  int term; /* Noeud terminal ou non */
  int x , y ; /* Coordonnees du noeud*/
  CellNoeud * voisins ; /* Liste des voisins du noeud */
} Noeud ;

/* Un reseau */
typedef struct {
  int nbNoeuds ; /*Nombre de noeuds du reseau */
  int nbAretes ; /*Nombre maximal de fibres par cable */
  CellNoeud * noeuds ; /*Liste des noeuds du reseau */
  CellCommodite * commodites ; /*Liste des commodites a relier */ 
} Reseau ;

Noeud *creerNoeud();
CellNoeud *creerlistenoeud();
CellCommodite *creerchCommodite();
Reseau *creerReseau();
void detruireReseau(Reseau *res);
Noeud * recherche_nd(Reseau *res , int num);
Reseau *lectureReseau(FILE *f);
int comptecable (Reseau *res);
void ecrireReseauTxt(Reseau *res, FILE *f);
void ecrireReseauDot(Reseau *res, FILE *f);
void afficheReseauGnuplot(Reseau *R, char* nomInstance);
void printReseau(Reseau *res);
void ajouteNoeudDansSuivant(Noeud *noeud1, Noeud *noeud2);

# endif

