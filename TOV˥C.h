#ifndef TOV˥C_H_INCLUDED
#define TOV˥C_H_INCLUDED

#define b 50

typedef enum {
  faux=0,
  vrai=1
} boolean;
/*--------------------structure de l'entete----------------------------------*/
typedef struct T_entete
{
    int num_dernier_bloc; // le numero du dernier bloc
}  T_entete ;
/*----------------structure de bloc------------------------------------*/

typedef struct T_bloc
{
    char tab[b];  // un tableau de b characteres
    int pos_libre;//la premiere podition libre dans le tableau
    char cle1[10],cle2[10];//la plus grande cle et la plus petite
}   T_bloc ;

/*----------------structure de fichier -------------------------------------*/
typedef struct TOVC_bar
{
    FILE * f ;
    T_entete entete;
}   TOVC_bar;



/************************************************************************************/
/*-----------------------LES FONCTIONS ET PROCEDURES--------------------------------*/

TOVC_bar *ouvrir(char nomfich[20],char mode);
void fermer(TOVC_bar *fichier);
void ecrire_dir(TOVC_bar *fichier,int i,T_bloc *buf);
void lire_dir(TOVC_bar *fichier,int i,T_bloc *buf);
void alloc_bloc(TOVC_bar *fichier);
int entete(TOVC_bar *fichier);
void aff_entete(TOVC_bar *fichier,int val);
void copy_enreg_buf(char enreg[b],T_bloc* buf,int position);
int recup_taille(char enreg[b]);
boolean depasse(char enreg[b],T_bloc *buf,int position);
char *recup_cle(char enreg[b]);



/*-------------------------------------------------------*/

TOVC_bar *initialisation(char nomfich[30],int nb_enreg);
void rech_dico(TOVC_bar *fichier,char cle[10],boolean i,boolean j,boolean trouv);
void insertion(TOVC_bar *fichier,char enreg[b]);


#endif // TOV˥C_H_INCLUDED
