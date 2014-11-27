#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reseau.h"
#include "tas_dijkstra.h"
#include "dijkstra.h"


int main(int argc, char *argv[]) {

  FILE *f=  NULL;
  FILE *gr = NULL;
  Reseau *res = NULL;
  Tas *tas;
#ifdef DEBUG
  int i;
#endif

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
  printf("Lecture reseau terminé.\n");

  /* Affichage en formt dot */
  ecrireReseauDot(res, gr);
  printf("Ecriture fichier dot terminé.\n");
  //system("neato -s -Tps -o graph.ps test.dot");

  //initialisation du tas à partir des noeuds du reseau
  tas = initTas(res);
  printf("Initialisation du tas terminée.\n");

#ifdef DEBUG
  afficher(tas);
#endif

  //creation du tas pour la premiere commodité
  dijkstra(tas, res, res->noeuds->cour); 
  printf("Calcul dijkstra terminée.\n");
  
#ifdef DEBUG
    for(i = 0; i<res->nbNoeuds; i++) {
      printf("%d.%d : %d -> %d\n", i, tas->val[i]->numero, 
	     tas->val[i]->precedent, tas->val[i]->poids);
    }
#endif

  return 0;
}
