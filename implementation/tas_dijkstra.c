#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "tas_dijkstra.h"
#include "reseau.h"

#define pere(i) ((i-1)/2)
#define droite(i) ((2*i)+2)
#define gauche(i) ((2*i)+1)

/* creer un element */
Elem *creerElem() 
{
  //nouvel element
  Elem *el = malloc (sizeof(Elem));

  //initialisation de sommet et clef a une valeur null;
  el->numero = -1;
  el->precedent = -1;
  el->poids = 0.0;
  el->noeud = NULL;
  el->posTas = -1;
  
#ifdef DEBUG
  printf("elem crée \n");
#endif
  return el;
}
  
  
/* creer un Tas*/
Tas *initialiser(int taille) {
  int i =0;
  
  //creation de la structure de tas et de ces fils
  Tas *tas = malloc (sizeof(Tas));

  tas->val = malloc(taille * sizeof(Elem*));
  tas->tas = malloc(taille * sizeof(int));

  //initialisation des tableaux
  for (i=0; i< taille; i++) {
    //    printf ("boucle \n");
    tas->val[i] = NULL;
    tas->tas[i] = -1;
  }

  tas->nbNoeud = 0;
  tas->nbMax = taille;

#ifdef DEBUG
  printf("tas de taille %d crée \n" , taille);
#endif
  
  return tas;
}

/* Remplir un tas à partir d'un réseau avec tous les noeux ayant une distance max */
Tas *initTas(Reseau *res) 
{
  Tas *tas;
  CellNoeud *n = NULL;
  Elem *el;

  //creer un tas de la taille du reseau
  tas = initialiser(res->nbNoeuds);
  
  //inserer tous les noeuds du reseau avec une distance max
  n = res->noeuds;

  while(n != NULL) {
    el = creerElem();
    remplirElem(el, n->cour, -1, FLT_MAX);

    ajouter(tas, el, FLT_MAX);
    n = n->suiv;
  }

  return tas;
}

void detruireTas(Tas *tas)
{
  if(tas != NULL) {
    free(tas->val);
    free(tas->tas);
    free(tas);
  }
}

/* initialiser un element avec les valeurs passées en arguments */
void remplirElem(Elem *el, Noeud *n, int precedent, double poids) {
  el->numero = n->num;
  el->precedent = precedent;
  el->poids = poids;
  el->noeud = n;
  
#ifdef DEBUG
  printf("remplissage de l'élement avec num %d, prec %d et %.03f\n", 
	 n->num , precedent, poids);
#endif
}

int compare(Tas *t, int i, int p)
{
  return (t->val[t->tas[i]]->poids <= t->val[t->tas[p]]->poids);
}

/* inserer un nouvel element dans le tas en le placant a la derniere position et en le faisant remonter */
void ajouter( Tas *t, Elem *el, double poids) 
{
  int i = 0;
  int p = 0;
  int s = 0;
    
  if(t->nbNoeud == t->nbMax) {
    printf("Tas plein");
    return;
  }

  el->poids = poids;

  //inserer l'élément dans le tableau des valeurs 
  t->val[el->numero] = el;
 
  //inserer le numero sur le haut du tas
  t->tas[t->nbNoeud] = el->numero;
  t->val[el->numero]->posTas = t->nbNoeud; 

  //trier le tas
  i = t->nbNoeud;
  while(i != 0 ) {
    p = pere(i);

#ifdef DEBUG
    printf("Ajouter i : %d  p : %d\n", i, p);
#endif

    if(compare(t, i, p)) {
      //swap de i et p
      s = t->tas[i];
      t->tas[i] = t->tas[p];
      t->tas[p] = s;
      
      //stocker la valeur dans le tas
      t->val[t->tas[p]]->posTas = p; 
      t->val[t->tas[i]]->posTas = i; 
     
      //remonter au pere 
      i = p;
    }
    else {
      //element plus grand que son pere, fini
      i = 0;
    }
  }
  
  //incrementer le nombre de noeuds
  t->nbNoeud++;
}

Elem *recup_min(Tas *tas)
{
  Elem *e;

  if(tas->nbNoeud == 0) {
    //tas vide
    e = NULL;
  }
  else {
    e = tas->val[tas->tas[0]];
    supprimer(tas, e);
  }

  return e;
}

Elem *rechercher(Tas *t, int idx) 
{  
  return (t->val[idx]);
}


void supprimer(Tas *t, Elem *el) { 
  int i = 0;
  int j, d, g, s;
  int idx = el->numero;

  if(t->val[idx] == NULL) {
#ifdef DEBUG
    printf("Le noeud n'existe pas.\n");
#endif
    return;
  }
  else {
    i = t->val[idx]->posTas;
  }

#ifdef DEBUG
  printf("Element trouve : %d\n", i);
#endif
  
  //decrementer le nombre de noeud
  t->nbNoeud--;

  if(i == t->nbNoeud) {
    //c'est le dernier élément l'effacer uniquement
    t->tas[t->nbNoeud] = -1;
    return;
  }

  //echanger le dernier noeud avec le noeud à supprimer 
  //et effacer le dernier noeud
  t->tas[i] = t->tas[t->nbNoeud];
  t->tas[t->nbNoeud] = -1;
  //stocker la valeur dans le tas
  t->val[t->tas[i]]->posTas = i; 
  
  //remonter du pere si il existe
  if(i != 0) {
    i = pere(i);
  }
  
  //reordonner tous les noeuds au dessous du pere
  while(i >= 0) {
    //initialiser le noeud a une valeur impossible
    j = -1;
    d = droite(i);
    g = gauche(i);
    if((d < t->nbNoeud) && compare(t, d, i)) {
      if(compare(t, g, d)) {
	//fils gauche existe et est le plus petit des deux fils
	j = g;
      }
      else {
	//fils droit existe et est plus petit que le pere
	j = d;
      }
    }
    else {
      if((g < t->nbNoeud) && compare(t, g, i)) {
	//fils gauche existe et est le plus petit que le pere
	j = g; 
      }
      //le pere est le plus petit arrêter
    }
    if(j>=0) {
      //il faut faire un swap avec le pére
      s = t->tas[i];
      t->tas[i] = t->tas[j];
      t->tas[j] = s;
      
      //stocker la valeur dans le tas
      t->val[t->tas[i]]->posTas = i; 
      t->val[t->tas[j]]->posTas = j; 
    }
    //j est le nouveau pére
    i = j;
  }
} 

void afficher (Tas* t) {
  int i = 0;

  printf("Nb noeud : %d\n", t->nbMax);

  while (i < t->nbMax) {
    /*    printf("posTas : %d, %d -> %.03f\n", t->val[t->tas[i]]->posTas,
	  t->val[t->tas[i]]->numero, t->val[t->tas[i]]->poids); */
    printf("posTas : (%d, %d) -> %d, %d -> %.03f\n", i, t->tas[i], t->val[i]->precedent,
	  t->val[i]->numero, t->val[i]->poids); 
    i++;
  }
}

int est_vide(Tas *t)
{
  return(t->nbNoeud == 0);
}

void miseAJour(Tas *t, Elem *el) 
{
  int i = 0;
  int p, s;

  if(t->val[el->numero] == NULL) {
#ifdef DEBUG
    printf("Le noeud n'existe pas.\n");
#endif
    return;
  }
  else {
    i = t->val[el->numero]->posTas;
  }

  while(i != 0 ) {
    p = pere(i);

#ifdef DEBUG
    printf("MaJ i : %d  p : %d\n", i, p);
#endif

    if(compare(t, i, p)) {
      //swap de i et p
      s = t->tas[i];
      t->tas[i] = t->tas[p];
      t->tas[p] = s;
      
      //stocker la valeur dans le tas
      t->val[t->tas[i]]->posTas = i; 
      t->val[t->tas[p]]->posTas = p; 
      
      //remonter au pere 
      i = p;
    }
    else {
      //element plus grand que son pere, fini
      i = 0;
    }
  }
}
