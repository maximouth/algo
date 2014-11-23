#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "lectGraph.h"
#include "generateurDot.h"

int main(int argc, char *argv[]) {

  FILE *f=  NULL;
  FILE *gr = NULL;
  char *nomfic;
  Graph *graph = NULL;
  if(argc != 3) {
    printf("Usage : Projet.x nom_fichier_entree nom_du_graph\n");
    exit(1);
  } 

/* Allocation pour le nom de fichier avec l'extension .tmp */
  nomfic = malloc(strlen(argv[1]));
  
  /* Ouverture du fichier d'entrée */
  strcpy(nomfic, argv[1]);
  printf("nom fichier : %s\n", nomfic);
  f = fopen(nomfic, "r");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomfic);
    exit(1);
  }
  
  gr = fopen(argv[2],"w");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", argv[2]);
    exit(1);
  }
  graph = lectGraph(f);
  generateur(gr,graph);
  //system("neato -Tps -o graph.ps test.dot");

  /*
  Point *p1 = creerPointTerm();
  Point *p2 = creerPointTerm();
  Point *p3 = creerPointTerm();
  Point *p4 = creerPointTerm();
  Point *p5 = creerPointTerm();
  Point *p6 = creerPointTerm();

  Graph *g = creerGraph(5);


  Voisin *v1 = creerArrete();
  Voisin *v2 = creerArrete();
  Voisin *v3 = creerArrete();
  Voisin *v4 = creerArrete();
  Voisin *v5 = creerArrete();
  Voisin *v6 = creerArrete();

  initVoisin(v1, "p1", 1);
  initVoisin(v2, "p2", 2);
  initVoisin(v3, "p3", 3);
  initVoisin(v4, "p4", 4);
  initVoisin(v5, "p5", 5);
  initVoisin(v6, "p6", 1);

  initPoint(p1, "p1", 0, 0);
  initPoint(p2, "p2", 0, 1);
  initPoint(p3, "p3", 0, 2);
  initPoint(p4, "p4", 0, 3);
  initPoint(p5, "p5", 0, 4);
  initPoint(p6, "p6", 0 ,5);

  ajouterPoint(g, p1);
  ajouterPoint(g, p2);
  ajouterPoint(g, p3);
  ajouterPoint(g, p4);
  ajouterPoint(g, p5);

  printf("p1 appartient a g? %d\n", appartient(g,p1)); 
  printf("p2 appartient a g? %d\n", appartient(g,p2)); 
  printf("p3 appartient a g? %d\n", appartient(g,p3)); 
  printf("p4 appartient a g? %d\n", appartient(g,p4)); 
  printf("p5 appartient a g? %d\n", appartient(g,p5)); 
  printf("p6 appartient a g? %d\n", appartient(g,p6)); 
  
  printf("\n\najout de voisins \n\n");
  ajouterVoisin(g, v1, p2);
  ajouterVoisin(g, v3, p1);
  ajouterVoisin(g, v1, p4);
  ajouterVoisin(g, v1, p5);
  
  ajouterVoisin(g, v2, p3);
  ajouterVoisin(g, v2, p4);
  ajouterVoisin(g, v2, p5);

  printf("cout entre %s et %s : %d \n",p1->nom ,p2->nom, CoutArrete(p1, p2));
  printf("cout entre %s et %s : %d \n",p2->nom ,p1->nom, CoutArrete(p2, p1));
  printf("cout entre %s et %s : %d \n",p1->nom ,p3->nom, CoutArrete(p1, p3));
  printf("cout entre %s et %s : %d \n",p1->nom ,p6->nom, CoutArrete(p1, p6));

  */

  

  return 0;

}
