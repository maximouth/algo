#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "lectGraph.h"
#include "generateurDot.h"

/*
 *
 * pour creer le graph utiliser cette commande :
 * neato -s -Tps -o test.ps -n test.dot&  
 *
 */


void generateur(FILE *f, Graph *g) {
  int i =0;



  fprintf(f,"graph g { \n\trankdir = LR\n\tbgcolor = grey50\nsize = \"1500\"\n");
  //xfprintf(f,"graph [bb=\"0,0,10000,10000\"]");
  fprintf(f,"\tnode [\n\tfrontsize = \"0.001\"\n\tstyle = \"rounded, filled\"\n\t]\n\n");
  
  for (i = 0; i< g->size ; i++) {
    fprintf(f,"\tmyNode%d [\n",i);
    fprintf(f,"\tlabel = \"%s\"\n",g->Point[i]->nom);
    fprintf(f,"\tcolor = blue\n");
    fprintf(f,"\tpos = \"%d,%d\"\n",g->Point[i]->x,g->Point[i]->y);
    fprintf(f,"\t]\n\n");
    }
  
  
  for (i = 0; i< g->size ; i++) {
    while (g->Point[i]->voisin) {

      if (atoi(g->Point[i]->voisin->nom) > atoi(g->Point[i]->nom)){

      fprintf(f,"\"myNode%s\" -- \"myNode%s\" [ \tpenwidth = 0.001 \n\t color = red\n\tlabel = \"%d\" ]\n",g->Point[i]->nom,g->Point[i]->voisin->nom,g->Point[i]->voisin->cout );
      }
    g->Point[i]->voisin = g->Point[i]->voisin->suiv;
      
    }
    } 
  

fprintf(f,"}");
}


