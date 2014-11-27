#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reseau.h"
#include "generateurDot.h"

/*
 *
 * pour creer le graph utiliser cette commande :
 * neato -s -Tps -o test.ps -n test.dot&  
 *
 */


void generateur(FILE *f, Reseau *res) {
  Point *p;
  Voisin *v;

  if(g == NULL) {
    printf("generateur : Graphe vide.\n");
    exit(0);
  }

  fprintf(f,"graph g { \n\trankdir = LR\n\tbgcolor = grey50\nsize = \"1500\"\n");
  //xfprintf(f,"graph [bb=\"0,0,10000,10000\"]");
  //fprintf(f,"\tnode [\n\tfrontsize = \"0.001\"\n\tstyle = \"rounded, filled\"\n\t]\n\n");
  
  p = g->points;
  while( p != NULL) {
    fprintf(f,"\tmyNode%s [\n",p->nom);
    fprintf(f,"\tlabel = \"%s\"\n",p->nom);
    fprintf(f,"\tcolor = blue\n");
    fprintf(f,"\tpos = \"%d,%d\"\n",p->x, p->y);
    fprintf(f,"\t]\n\n");
    p = p->suivant;
    }
  
  p = g->points;
  while( p != NULL) {
    v = p->voisin;
    while (v != NULL) {
      if (atoi(p->nom) > atoi(v->point->nom)){
	fprintf(f,"\"myNode%s\" -- \"myNode%s\" [ \tpenwidth = 0.001 \n\t color = red\n\tlabel = \"%d\" ]\n",p->nom, v->point->nom, v->cout );
      }
      v = v->suivant;
    }
    p = p->suivant;
  } 
  
fprintf(f,"}");
}


