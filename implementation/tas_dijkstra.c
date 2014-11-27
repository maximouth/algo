#include <stdio.h>
#include <stdlib.h>

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
  el->poids = 0;
  el->noeud = NULL;
  el->posTas = -1;
  
#ifdef DEBUG
  printf("elem crée \n");
#endif
  return el;
}
  
  
/* creer un Tas*/
Tas *creerTas(int taille) {
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

/* initialiser un element avec les valeurs passées en arguments */
void remplirElem(Elem *el, Noeud *n, int precedent, int poids) {
  el->numero = n->num;
  el->precedent = precedent;
  el->poids = poids;
  el->noeud = n;
  
#ifdef DEBUG
  printf("remplissage de l'élement avec num %d, prec %d et %d\n", 
	 n->num , precedent, poids);
#endif
}

int compare(Tas *t, int i, int p)
{
  return (t->val[t->tas[i]]->poids < t->val[t->tas[p]]->poids);
}

/* inserer un nouvel element dans le tas en le placant a la derniere position et en le faisant remonter */
void inserer( Tas *t, Elem *el) 
{
  int i = 0;
  int p = 0;
  int s = 0;

  if(t->nbNoeud == t->nbMax) {
    printf("Tas plein");
    return;
  }

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
    printf("i : %d  p : %d\n", i, p);
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

Elem *minimum(Tas *t)
{
  Elem *e;

  if(t->nbNoeud == 0) {
    //tas vide
    e = NULL;
  }
  else {
    e = t->val[t->tas[0]];
  }

  return e;
}

Elem *rechercher(Tas *t, int idx) 
{  
  return (t->val[idx]);
}


void supprimer (Tas *t, int idx) { 
  int i = 0;
  int j, d, g, s;

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

  printf("Nb noeud : %d\n", t->nbNoeud);

  while (i < t->nbNoeud) {
    printf("posTas : %d, %d -> %d\n", t->val[t->tas[i]]->posTas,
	   t->val[t->tas[i]]->numero, t->val[t->tas[i]]->poids);
    i++;
  }
}

int tasVide(Tas *t)
{
  return(t->nbNoeud == 0);
}

void marquer(Tas *t, int idx)
{
  //supprimer le noeud du tas
  supprimer(t, idx);
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
    printf("i : %d  p : %d\n", i, p);
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
