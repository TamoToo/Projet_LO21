#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//Déclaration de la liste pour seau
typedef struct seau{
    struct seau *next;
    char* nombre;
}seau;

typedef seau *List;

typedef struct list_seau{
    char num[1];
    seau *liste_chiffre;
}list_seau;

List ajout_fin(List l, char * c);
List supprimer_tete(List l);
void afficher_list(List l, char numero_seau);
void afficher_seaux(int base, list_seau T[]);
void show_string(int nbval, char** tableau);
void reverse_string(char* string);
int ctoi(char caractere);
char itoc(int nombre);
char* baseToBase(char* nombre_entree, int base_entree, int base_sortie);
int equalize(int nbval,char** tableau);
void viderBuffer();
int read_stdin(char *chaine, int longueur);