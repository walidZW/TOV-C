/*********************************************IMPLEMENTATION DES FONCTIONS*****************************************/
#include "TOV˥C.h"
#include <string.h>

TOVC_bar * ouvrir (char nomfich[30], char mode)
{
    TOVC_bar * fichier = malloc(sizeof(TOVC_bar));


    if ((mode== 'n')||(mode== 'N'))
    {
        fichier->f = fopen(nomfich,"wb+") ;
        if (fichier->f != NULL){

            printf("le fichier a été bien crée\n");
            fichier->entete.num_dernier_bloc=0;
            rewind(fichier->f);
            fwrite(&(fichier->entete),sizeof(T_entete),1,fichier->f);

        }
        else {printf("fichier mal cree\n");}
    }


    else
    {
        if ((mode == 'a')||(mode == 'A'))
        {
            fichier->f = fopen(nomfich,"rb+");
            if (fichier->f!= NULL)
            {
            printf(" le fichier a été bien crée\n");

                rewind(fichier->f);
                fread(&(fichier->entete),sizeof(T_entete),1,fichier->f);

            }
            else {printf(" fichier mal ouvert, creer le fichier avant de continuer\n");}
        }
    }


    return(fichier);
}

/*-------------------------------------------------------------------------------------------*/
void fermer(TOVC_bar *fichier){

    rewind(fichier->f);
    fwrite(&(fichier->entete),sizeof(T_entete),1,fichier->f);
    fclose(fichier->f);
    free(fichier);
}
/*-------------------------------------------------------------------------------------------*/
void ecrire_dir(TOVC_bar *fichier,int i,T_bloc *buf){

        fseek(fichier->f,sizeof(T_entete)+(sizeof(T_bloc)*(i-1)),SEEK_SET);
        fwrite(&buf,sizeof(T_bloc),1,fichier->f);
}
/*-------------------------------------------------------------------------------------------*/
void lire_dir(TOVC_bar *fichier,int i,T_bloc *buf){

        fseek(fichier->f,sizeof(T_entete)+(sizeof(T_bloc)*(i-1)),SEEK_SET);
        fread(buf,sizeof(T_bloc),1,fichier->f);
}
/*---------------------------------------------------------------------------------------------*/
void alloc_bloc(TOVC_bar *fichier){

aff_entete(fichier,entete(fichier)+1);

}

/*-------------------------------------------------------------------------------------------*/
int entete(TOVC_bar *fichier){
return fichier->entete.num_dernier_bloc;
}

/*------------------------------------------------------------------------------------------*/
void aff_entete(TOVC_bar *fichier,int val){
fichier->entete.num_dernier_bloc=val;

}
/*----------------------------------------------------------------------------------------*/

TOVC_bar *initialisation(char nomfich[30],int nb_enreg){

    int i;
    char enreg[80];
    TOVC_bar *fichier=ouvrir(nomfich,'n');
    aff_entete(fichier,1);
    T_bloc *buf;
    printf("\njghgrkthgkihtik");
   // buf->pos_libre=0;

    ecrire_dir(fichier,entete(fichier),buf);

    for(i=0;i<nb_enreg;++i){
        printf("entrer l'enregestrement\n\n");
        scanf("%s",enreg);
        insertion(fichier,enreg);
        printf("%s",enreg);
        }

    return fichier;
    }

/*-------------------------------------------------------------------------------------*/
void rech_dico(TOVC_bar *fichier,char cle[10],boolean i,boolean j,boolean trouv){
   int bs,bi,f,inf,sup;
   char cle_temp[10];
   T_bloc *buf;
   boolean stop=faux;
   bs=entete(fichier);
   bi=1;
   j=0;

   trouv=faux;
   while((bi<=bs) && !(trouv) && !(stop)){

           i=(bi+bs) / 2;
           lire_dir(fichier,i,buf);

           if((strcmp(cle,buf->cle1)>=0) && (strcmp(cle,buf->cle2)<=0)){//si cle est entre cle1 et cle2 alors recherche devient sequentielle
                 while(j+10<buf->pos_libre){
                     for(f=0;f<10;++f){
                         cle_temp[f]=buf->tab[j+f];

                     }
                     ++j;
                     if(strcmp(cle,cle_temp)==0){trouv=vrai;}

                 }


           }else{//si la cle n'est pas entre cle1 et cle2
             if(strcmp(cle,buf->cle1)<0){
                bs=i-1;}
             if(strcmp(cle,buf->cle2)>0){
                bi=i+1;
                }
                }

     }
     if(!trouv){
        printf("cette clé n'a pas été trouvé");

     }else{
     printf("la clé a été bien trouvé\n");
     printf("bloc %d\n",i);
     printf("position %d\n",j);
     }


}
/*------------------------------------------------------------------------------------*/
void insertion(TOVC_bar *fichier,char enreg[b]){

   T_bloc *buf;
   int cmp1,cmp2;
   lire_dir(fichier,fichier->entete.num_dernier_bloc,buf);
   if(!depasse(enreg,buf,buf->pos_libre)){
          copy_enreg_buf(enreg,buf,buf->pos_libre);
          buf->pos_libre=(buf->pos_libre)+(recup_taille(enreg));
          cmp1=strcmp(recup_cle(enreg),buf->cle1);
          cmp2=strcmp(recup_cle(enreg),buf->cle2);
          if(cmp1<0){
                strcpy(buf->cle1,recup_cle(enreg));}
          if(cmp2>0){
                strcpy(buf->cle2,recup_cle(enreg));}

   }else{ // si on depasse la taille max du tab
          alloc_bloc(fichier);
          aff_entete(fichier,entete(fichier)+1);
          strcpy(buf->cle1,recup_cle(enreg));
          strcpy(buf->cle2,recup_cle(enreg));
          buf->pos_libre=recup_taille(enreg);
          copy_enreg_buf(enreg,buf,0);
          ecrire_dir(fichier,entete(fichier),buf);
    }
    ecrire_dir(fichier,entete(fichier),buf);
}
/*--------------------------------------------------------------*/
void copy_enreg_buf(char enreg[b],T_bloc* buf,int position){
int i=0;

while(enreg[i] != '$'){
    buf->tab[position+i]=enreg[i];
    ++i;
}
}

/*----------------------------------------------------------------*/
int recup_taille(char enreg[b]){
int taille=(enreg[0]*100)+(enreg[1]*10)+(enreg[2]);
return taille;
}
/*-----------------------------------------------------------------*/
boolean depasse(char enreg[b],T_bloc *buf,int position)
{
   boolean dep=faux;
   int tai=recup_taille(enreg);
   int test_taille=position+tai;
   if(test_taille>b){
    dep=vrai;
}
   return dep;
}
/*-----------------------------------------------------*/
char *recup_cle(char enreg[b]){
char recup_cle[10];
for(int i=0;i<10;++i){
recup_cle[i]=enreg[4+i];
}
return recup_cle;
}
/*-------------------------------------------------------*/













