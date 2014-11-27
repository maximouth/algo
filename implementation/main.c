#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reseau.h"


int main(int argc, char *argv[]) {

  FILE *f=  NULL;
  FILE *gr = NULL;
  Reseau *res = NULL;

  if(argc != 3) {
    printf("Usage : Projet.x nom_fichier_entree nom_du_graph\n");
    exit(1);
  } 

  /* Ouverture du fichier d'entrée */
  printf("nom fichier : %s\n", argv[1]);
  f = fopen(argv[1], "r");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", argv[1]);
    exit(1);
  }
  
  /* Ouverture du fichier de sortie */
  printf("nom fichier : %s\n", argv[2]);
  gr = fopen(argv[2],"w");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", argv[2]);
    exit(1);
  }

  /* Lecture du reseau */
  res = lectureReseau(f);

  /* Affichage en formt dot */
  ecrireReseauDot(res, gr);
  //system("neato -Tps -o graph.ps test.dot");

  return 0;
}
