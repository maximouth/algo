#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entree_sortie.h"
#include "reseau.h"

#define MAX_TAILLE_LECTURE 100

Noeud *creerNoeud () {

// Noeud du reseau
Noeud *noeud;

 noeud = (Noeud *)malloc(sizeof(Noeud));
 //initialisation du numero et des coordonée du noeud a 0
 noeud->num=0; 
 noeud->x=0; 
 noeud->y=0; 
 
 noeud->voisins=NULL;

#ifdef DEBUG
 printf ("noeud crée\n");
#endif
 
 return noeud;
}
  
CellNoeud *creerlistenoeud () {
  
  /* liste chainée de noeuds */
  CellNoeud *cnd;
  cnd = (CellNoeud*)malloc (sizeof( CellNoeud));
  
  // initialisation du noeud courant
  cnd->cour = NULL;
  
  // initialisation du noeud suiv
  cnd->suiv = NULL;
  
  return cnd;
}

CellCommodite *creerchCommodite() {
  
  //liste chainée de commodité
  CellCommodite *ccm;
  ccm =(CellCommodite*) malloc (sizeof (CellCommodite));
  
  //initialisation des extremités de la commodité
  ccm-> extrA = NULL;
  ccm-> extrB = NULL;
  
  //initialisation de la cellule suivante dans la liste
  ccm->suiv =NULL;
  
#ifdef DEBUG
  // printf ("Liste chainee de commodite crée\n");
#endif
  
  return ccm;
}

Reseau *creerReseau() {
  Reseau *new_res;

  new_res = (Reseau *)malloc(sizeof(Reseau));

  //initialisation des champs de la structure reseau
  new_res->nbNoeuds = 0;
  new_res->nbAretes = 0;
  new_res->noeuds = NULL;
  new_res->dep = NULL;
  new_res->commodites = NULL;

#ifdef DEBUG
  printf ("Reseau  créé\n");
#endif

  return(new_res);
}

void detruireNoeuds(CellNoeud *n) 
{
  CellNoeud *tmp1, *tmp2;
  
  tmp1 = n;
  while(tmp1 != NULL) {
    free(tmp1->cour);
    tmp2 = tmp1;
    free(tmp2);
    tmp1 = tmp1->suiv;
  }
}

void detruireCommodite(CellCommodite *com) 
{
  CellCommodite *tmp1, *tmp2;
  
  tmp1 = com;
  while(tmp1 != NULL) {
    tmp2 = tmp1;
    free(tmp2);
    tmp1 = tmp1->suiv;    
  }
}

void detruireReseau(Reseau *res) 
{
  detruireNoeuds(res->noeuds);
  detruireCommodite(res->commodites);
  free(res);
}


Noeud * recherche_nd(Reseau *res , int num) {
  CellNoeud *celnoeud = res->noeuds;
  Noeud *nd = NULL;
  
  while (celnoeud != NULL) {
    nd = celnoeud->cour;

    if(nd == NULL) {
#ifdef DEBUG
      printf("Acces à une cellule non initialisée\n");
#endif
      return(NULL);
    }

    if(nd->num == num){
#ifdef DEBUG
      printf("noeud num %d trouvé\n" ,num);
#endif
      return nd;
    }

    /* Passage au noeud suivant */
    celnoeud = celnoeud->suiv;
  }
  
#ifdef DEBUG
  printf ("le noeud recherché n'existe pas\n");
#endif
  return(NULL);
}

Reseau *lectureReseau(FILE *f) {

  Reseau *res = creerReseau();
  CellNoeud *noeuds = NULL;
  Noeud *nd = NULL;
  char s[MAX_TAILLE_LECTURE];
  int nb = 0;
  int cptnb = 0;
  double poids = 0;

  Noeud *ndtmp1 = NULL;
  Noeud *ndtmp2 = NULL;
  CellNoeud *celltmp1 = NULL;
  CellNoeud *celltmp2 = NULL;

 //lire le nombre de points  
  GetChaine (f, MAX_TAILLE_LECTURE , s);
  res->nbNoeuds = atoi(s);
#ifdef DEBUG
  printf("%d\n" ,res->nbNoeuds);
#endif
  
  //lire le nombre d'aretes
  GetChaine (f, MAX_TAILLE_LECTURE , s);
  res->nbAretes = atoi(s);
#ifdef DEBUG
  printf("%d \n" ,res->nbAretes);
#endif
  
  nb = res->nbNoeuds;
  while (cptnb < nb) {
    //création et positionnement du noeud courant
    noeuds = creerlistenoeud();
    noeuds->cour = creerNoeud();
   if(res->noeuds == NULL) {
      /* Premier noeud de la liste */
      res->noeuds = noeuds;
      res->dep = noeuds->cour;
    }
    else {
      /* Inserer un autre noeud */
      noeuds->suiv = res->noeuds;
      res->noeuds = noeuds;
    }

    noeuds->cour = creerNoeud();
    nd = noeuds->cour;
        
    //lecture du numero du noeuds
    GetChaine (f, MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf("num noeud %s ", s);
#endif
    nd->num = atoi(s);

    //savoir si point terminal ou pas
    GetChaine(f, MAX_TAILLE_LECTURE, s);
#ifdef DEBUG
    printf("terminal? : %s \n",s);
#endif
    nd->term = atoi(s);

    //lecture des coordonnées du noeud
    GetChaine (f, MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf("%s ", s);
#endif
    nd->x = atof(s);

    GetChaine (f, MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf("%s \n", s);
#endif
    nd->y = atof(s);

#ifdef DEBUG    
printf ("nb = %d \ncptnb = %d\n", nb ,cptnb);
#endif
    cptnb++;
  }
  

  nb = res->nbAretes;
  cptnb = 0;
  while ( cptnb < nb)  {
    //1er point
    GetChaine (f , MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf ("%s " ,s);
#endif
    ndtmp1= recherche_nd( res, atoi(s));      
    
    //2eme point
    GetChaine (f , MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf ("%s ->" ,s);
#endif
    ndtmp2 = recherche_nd(res ,atoi(s));

    //type de la struct
    GetChaine (f , MAX_TAILLE_LECTURE , s);
#ifdef DEBUG
    printf ("%s\n",s);
#endif
    poids = atof(s);
    
    //Chainage du voisin du noeud 1
    celltmp1 =creerlistenoeud();
    celltmp1->cour = ndtmp2;
    celltmp1->suiv = ndtmp1->voisins;
    ndtmp1->voisins = celltmp1;
    celltmp1->poids = poids;
    
    //Chainage du voisin du noeud 2
    celltmp2 =creerlistenoeud();
    celltmp2->cour = ndtmp1;
    celltmp2->suiv = ndtmp2->voisins;
    ndtmp2->voisins = celltmp2;
    celltmp2->poids = poids;

    cptnb++;
  }
  
#ifdef DEBUG
    printf ("\n");
#endif
  
  return res;
}  


int comptecable (Reseau *res) {
  
  int nb = 0;
  CellNoeud *ch = NULL;
  Noeud *noeud = NULL;
  CellNoeud *cable = NULL;
  
  if (res == NULL) {
    printf("comptecable : Erreur reseau vide.\n");
    return(-1);
  }
  
  /* Initialisation de la liste des noeuds */
  ch = res->noeuds;
  
  if (ch == NULL) {
    printf("comptecable : Erreur reseau sans noeud.\n");
    return(0);
  } 
    
  while (ch != NULL) {
    noeud = ch->cour;
    if(noeud == NULL) {
      printf("comptecable : Erreur noeud vide.\n");
      return(-1);
    }

  cable = noeud->voisins;
#ifdef DEBUG
  printf("Noeud : %d -> ", noeud->num);
#endif

  while (cable != NULL) {
#ifdef DEBUG
    printf ("%d, " , cable->cour->num);
#endif
    nb++;
    cable = cable->suiv;
  }

#ifdef DEBUG
  printf("\n");
#endif
    ch = ch->suiv;
  }
  
  /* Les cables sont comptés 2 fois (un fois par extrémité */
  nb = nb / 2;
  
  printf("il y a %d cables\n", nb);
  
  return(nb);
}
    
void ecrireReseauTxt(Reseau *res, FILE *f) 
{
  CellNoeud *noeuds = NULL;  
  CellNoeud *voisin = NULL;  
  CellCommodite *commodite = NULL;

  if(res == NULL) {
    printf("EcrireReseauTxt : Erreur réseau vide\n");
    return;
  }
    
  if(f == NULL) {
    printf("EcrireReseauTxt : Fichier de sortie non ouvert.\n");
    return;
  }

  /* Entete du fichier */
  fprintf(f, "NbNoeuds: %d\n", res->nbNoeuds);
  fprintf(f, "NbAretes: %d\n\n", res->nbAretes);
  
  /* Ecriture des coordonnées des noeuds */
  noeuds = res->noeuds;
  while(noeuds != NULL) {
    fprintf(f, "%d ", noeuds->cour->num);
    fprintf(f, "%.d ", noeuds->cour->x);
    fprintf(f, "%.d\n", noeuds->cour->y);
    
    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }

  fprintf(f, "\n");

  /* Ecriture des aretes, repartir du noeud de départ */
  noeuds = res->noeuds;
  while (noeuds != NULL) {
    /* parcourir ces voisins */
    voisin = noeuds->cour->voisins;
    while (voisin != NULL) {
      if(noeuds->cour->num > voisin->cour->num) {
        /* Afficher les voisins que dans un sens */
        fprintf(f, "a %d %d\n", noeuds->cour->num, voisin->cour->num);
      }

      /* Passage au voisin suivant */
      voisin = voisin->suiv;
    }

    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }

  fprintf(f, "\n");

  /* Ecriture de la liste des commodités */
  commodite = res->commodites;
  while(commodite != NULL) {
    fprintf(f, "o %d %d\n", commodite->extrA->num, commodite->extrB->num);
    /* Pasage à la commodite suivante */
    commodite = commodite->suiv;
  }
}

void ecrireReseauDot(Reseau *res, FILE *f) 
{
  CellNoeud *noeuds = NULL;  
  CellNoeud *voisin = NULL;  
  CellCommodite *commodite = NULL;

  if(res == NULL) {
    printf("EcrireReseauTxt : Erreur réseau vide\n");
    return;
  }
    
  if(f == NULL) {
    printf("EcrireReseauTxt : Fichier de sortie non ouvert.\n");
    return;
  }

  /* Entete du fichier */
  fprintf(f,"graph g { \n\trankdir = LR\n\tbgcolor = grey50\n\tsize = \"1500\"\n\n");
  
  /* Ecriture des coordonnées des noeuds */
  noeuds = res->noeuds;
  while(noeuds != NULL) {
    fprintf(f,"\tmyNode%d [\n", noeuds->cour->num);
    fprintf(f,"\tlabel = \"%d\"\n", noeuds->cour->num);
    if(noeuds->cour->term == 1)
      fprintf(f,"\tcolor = blue\n");
    else
      fprintf(f,"\tcolor = green\n");      
    fprintf(f,"\tpos = \"%d,%d\"\n",noeuds->cour->x, noeuds->cour->y);
    fprintf(f,"\t]\n\n");
    
    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }

  fprintf(f, "\n");

  /* Ecriture des aretes, repartir du noeud de départ */
  noeuds = res->noeuds;
  while (noeuds != NULL) {
    /* parcourir ces voisins */
    voisin = noeuds->cour->voisins;
    while (voisin != NULL) {
      if(noeuds->cour->num > voisin->cour->num) {
        /* Afficher les voisins que dans un sens */
	fprintf(f,"\"myNode%d\" -- \"myNode%d\" [ \tpenwidth = 0.001 \n\t color = red\n\tlabel = \"%f\" ]\n",noeuds->cour->num, voisin->cour->num, voisin->poids );
      }

      /* Passage au voisin suivant */
      voisin = voisin->suiv;
    }

    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }

  fprintf(f,"\n}\n");

  /* Ecriture de la liste des commodités */
  commodite = res->commodites;
  while(commodite != NULL) {
    fprintf(f, "o %d %d\n", commodite->extrA->num, commodite->extrB->num);
    /* Pasage à la commodite suivante */
    commodite = commodite->suiv;
  }
}

void genereFicGnuplot(char *nomInstance, int n, double x1, double y1,
		      double x2, double y2) {
  char *nomFic;
  FILE *f = NULL;

  nomFic = malloc(strlen(nomInstance)+10);
  sprintf(nomFic, "%s_%04d.txt", nomInstance, n);

  f = fopen(nomFic, "w");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }

  fprintf(f, "%.02f %.02f\n", x1, y1);
  fprintf(f, "%.02f %.02f\n", x2, y2);
 
  fclose(f); 
}

void genereComGnuplot(char *nomInstance, CellCommodite *com) {
  char *nomFic;
  FILE *f = NULL;
  CellCommodite *comx = com;

  nomFic = malloc(strlen(nomInstance)+10);
  sprintf(nomFic, "%s_com.txt", nomInstance);

  f = fopen(nomFic, "w");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }
 
  while(comx != NULL) {
    /* Affichage des extremites des commodites */
    fprintf(f, "%.d %d\n", comx->extrA->x, comx->extrA->y);
    fprintf(f, "%.d %d\n", comx->extrB->x, comx->extrB->y);
    
    /* Passage à la commodité suivante */
    comx = comx->suiv;
  }

  fclose(f); 

}

void GenereLoadGNuplot(char *nomInstance, int n) {
  char *nomFic;
  FILE *f = NULL;
  int i = 0;

  nomFic = malloc(strlen(nomInstance)+4);
  sprintf(nomFic, "%s.plt", nomInstance);

  f = fopen(nomFic, "w");
  if (f== NULL) {
    printf("Impossible d'ouvrir le fichier : %s.\n", nomFic);
    exit(1);
  }

  /* Generation de l'entete */
  fprintf(f, "set title \"%s\"\n", nomInstance);
  fprintf(f, "set xlabel \"X\"\n");
  fprintf(f, "set ylabel \"Y\"\n");
  fprintf(f, "set grid\n");
  fprintf(f, "unset key\n\n");

  /* Affichage du premier couple */
  fprintf(f, "plot \"%s_%04d.txt\" using 1:2 with lines\n", nomInstance, 0);

  for( i=1; i<n; i++) {
    /* Affichage des couples suivants */
    fprintf(f, "replot \"%s_%04d.txt\" using 1:2 with lines\n", nomInstance, i);
  }

  /* Affichage des commodités */
  fprintf(f, "replot \"%s_com.txt\" using 1:2 with points\n", nomInstance);

  /* Generation fin */
  fprintf(f, "set terminal png\n");
  fprintf(f, "set output \"%s.png\"\n", nomFic);
  fprintf(f, "replot\n");

  fclose(f); 
}


void afficheReseauGnuplot(Reseau *res, char* nomInstance) {
  CellNoeud *noeuds = NULL;  
  CellNoeud *voisin = NULL;
  int n = 0;

  if(res == NULL) {
    printf("afficheReseauGnuplot : Erreur réseau vide\n");
    return;
  }

  /* Ecriture des aretes, repartir du noeud de départ */
  noeuds = res->noeuds;
  while (noeuds != NULL) {
    /* parcourir ces voisins */
    voisin = noeuds->cour->voisins;
    while (voisin != NULL) {
      if(noeuds->cour->num > voisin->cour->num) {
        /* Afficher les aretes de voisins que dans un sens */
	genereFicGnuplot(nomInstance, n, noeuds->cour->x, noeuds->cour->y, 
			 voisin->cour->x, voisin->cour->y);
	n++;
      }
      
      /* Passage au voisin suivant */
      voisin = voisin->suiv;
    }

    /* Passage au noeud suivant */
    noeuds = noeuds->suiv;
  }
  
  /* Generation des extremités des commodités */
  genereComGnuplot(nomInstance, res->commodites);

  /* Generation du fichier de commande Gnuplot */
  GenereLoadGNuplot(nomInstance, n);
}

void printReseau(Reseau *res) {
  CellNoeud *n = res->noeuds;
  CellCommodite *com = res->commodites;
  CellNoeud *voisin = NULL;

  printf("NbNoeuds : %d, NbAretes : %d\n", res->nbNoeuds, res->nbAretes);
  
  while(n != NULL) {
    printf("(%d, %d)\n", n->cour->x, n->cour->y);
    voisin = n->cour->voisins;
    while(voisin != NULL) {
      printf("  -> (%d, %d)\n", voisin->cour->x, voisin->cour->y);
      voisin = voisin->suiv;
    }
    n = n->suiv;
  }

  printf("Com :\n");
  while(com != NULL) {
    printf("(%d, %d) * (%d, %d)\n", com->extrA->x, com->extrA->y,
	   com->extrB->x, com->extrB->y);
    com = com->suiv;
  }
}


int estdans (Noeud *nd1, Noeud *nd2) {
  CellNoeud *tmp = nd1->voisins;

  while (tmp != NULL) {
    if (tmp->cour->x == nd2->x && tmp->cour->y == nd2->y) {
      return 1;
    }
    tmp = tmp->suiv;
  }
  return 0;
}

void ajouteNoeudDansSuivant(Noeud *noeud1, Noeud *noeud2)
{
  CellNoeud * voisin = NULL;
  int test=0;  

  /* Ajout dans le noeud 1 */
  test = estdans(noeud1, noeud2);
  if (test == 0) {
    voisin = creerlistenoeud();
    voisin->cour = noeud2;
    voisin->suiv =  noeud1->voisins;
    noeud1->voisins = voisin;
  }


  /* Ajout dans le noeud 2 */
  test = estdans (noeud2, noeud1);
  if (test == 0) {
    voisin = creerlistenoeud();
    voisin->cour = noeud1;
    voisin->suiv =  noeud2->voisins;
    noeud2->voisins = voisin;
  }

#ifdef DEBUG
  printf("%d lien vers %d\n", noeud1->num, noeud2->num);
  printf("(%d, %d) lien vers (%d, %d)\n", 
         noeud1->x, noeud1->y, noeud2->x ,noeud2->y);
#endif
}
