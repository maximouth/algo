#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "reseau.h"
#include "tas_dijkstra.h"
#include "dijkstra.h"
#include "prim.h"
#include "graphe_distance.h"
#include "steiner.h"


int main(int argc, char *argv[]) {

  FILE *f=  NULL;
  Reseau *res = NULL;
  Reseau *gd = NULL;
  Reseau *st = NULL;
  Tas *tas;
  Prim *resPrim;
  char *nomFic;

  clock_t tmp_initial;
  clock_t tmp_final;

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
  


  /* Lecture du reseau */
  res = lectureReseau(f);
  fclose(f);
  printf("Lecture reseau terminé.\n");

  /* Ouverture du fichier de sortie */
  printf("nom fichier : %s\n", argv[2]);
  f = fopen(argv[2],"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", argv[2]);
    exit(1);
  }

  /* Affichage en forme dot */
  ecrireReseauDot(res, f);
  printf("Ecriture fichier dot terminé.\n");
  fclose(f);

  //system("neato -s -Tps -o graph.ps -n test.dot");

  //initialisation du tas à partir des noeuds du reseau
  tas = initTas(res);
  printf("Initialisation du tas terminée.\n");

#ifdef DEBUG
  afficher(tas);
#endif

  // Appel de Dijkstra sur le noeud de départ
  dijkstra(tas, res, res->dep); 
  printf("Calcul dijkstra terminé.\n");

  /* Ouverture du fichier de sortie */
  nomFic = malloc(strlen(argv[2])+4);
  strcpy(nomFic, argv[2]);
  strcat(nomFic, "Dij");
  printf("nom fichier : %s\n", nomFic);
  f = fopen(nomFic,"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }
  
  afficheDij(tas, res, f);
  fclose(f);

#ifdef DEBUG
    for(i = 0; i<res->nbNoeuds; i++) {
      printf("%d.%d : %d -> %.03f\n", i, tas->val[i]->numero, 
	     tas->val[i]->precedent, tas->val[i]->poids);
    }
#endif

  //initialisation du tas à partir des noeuds du reseau
  detruireTas(tas);
  tas = initTas(res);
  printf("Initialisation du tas terminée.\n");

  tmp_initial = clock();
  // Appel de Prim sur le noeud de départ
  resPrim = prim(tas, res, res->dep); 
  tmp_final= clock();
  printf("Calcul Prim terminé en %f\n",((double)(tmp_final - tmp_initial)/CLOCKS_PER_SEC) );

  printf("Poids arbre : %.03f\n", calculPoids(resPrim, res));

#ifdef DEBUG
  for(i = 0; i<res->nbNoeuds; i++) {
    printf("%d : %d -> %.3f\n", i, resPrim->pred[i], resPrim->d[i]);
  }
#endif
  /* Ouverture du fichier de sortie */
  strcpy(nomFic, argv[2]);
  strcat(nomFic, "Pri");
  printf("nom fichier : %s\n", nomFic);
  f = fopen(nomFic,"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }
    
  affichePrim(resPrim, res, f);
  fclose(f);

  /* Construction du graphe distance */
  gd = grapheDistance(res);

  /* Ouverture du fichier de sortie */
  strcpy(nomFic, argv[2]);
  strcat(nomFic, "GD");
  printf("nom fichier : %s\n", nomFic);
  f = fopen(nomFic,"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }

  ecrireReseauDot(gd, f); 
  fclose(f);

   //initialisation du tas à partir des noeuds du reseau
  detruireTas(tas);
  tas = initTas(gd);

  printf("Initialisation du tas terminée.\n");
 
  resPrim = prim(tas, gd, gd->dep); 
  printf("Calcul Prim graphe distance terminé.\n");

  /* Ouverture du fichier de sortie */
  strcpy(nomFic, argv[2]);
  strcat(nomFic, "Pgd");
  printf("nom fichier : %s\n", nomFic);
  f = fopen(nomFic,"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }
    
  affichePrim(resPrim, gd, f);
  fclose(f);

  st = steiner(resPrim, res);
  
   /* Ouverture du fichier de sortie */
  strcpy(nomFic, argv[2]);
  strcat(nomFic, "ST");
  printf("nom fichier : %s\n", nomFic);
  f = fopen(nomFic,"w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }

  ecrireReseauDot(st, f); 
  fclose(f);

   //initialisation du tas à partir des noeuds du reseau
  detruireTas(tas);
  tas = initTas(st);

  printf("Initialisation du tas terminée.\n");
 
  resPrim = prim(tas, st, st->dep); 
  printf("Calcul Prim graphe distance terminé.\n");

  printf("Poids arbre : %.03f\n", calculPoids(resPrim, st));


  return 0;
}
