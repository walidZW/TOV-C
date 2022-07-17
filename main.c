#include <stdio.h>
#include <stdlib.h>
#include "TOV˥C.h"
#include "TOV˥C.c"



int main()
{   int choix;
    int nb_enreg;
    TOVC_bar *fich;
    char nomfich2[20];
    char nomfich1[30];
    char cle[10];
    boolean i,j,trouv;
    printf("***********************************EXERCICE 8 (TOV˥C)*************************** \n");
    printf("1-INITIALISER UN NOUVEAU FICHIER\n");
    printf("2-FAIRE UNE RECHERCHE DICHOTOMIQUE SUR UN FICHIER EXISTANT\n");
    scanf("%d",&choix);
    if(choix==1){
        printf("donner le nom du fichier  ");
        scanf("%s",nomfich1);
        printf("donner le nombre d'enrgestrement a l'initialisation");
        scanf("%d",&nb_enreg);
        initialisation(nomfich1,nb_enreg);

    }
    if(choix ==2){
        printf("donner le nom du fichier\n");
        scanf("%s",nomfich2);
        fich=ouvrir(nomfich2,'a');
        rech_dico(fich,cle,i,j,trouv);
    }


}

