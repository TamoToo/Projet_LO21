#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "main_functions.h"


int main(int argc, char *argv[]) {

    int base, nbval, nbcaract, nombre_decimal;
    char buffer[10];

    printf("\n Veuillez entrer la base de vos nombres:");
    read_stdin(buffer, 10);
    base = strtol(buffer, NULL, 10);

    while (base < 2 || base > 16) {
        printf("\n Veuillez entrer une base comprise entre 2 et 16! : ");
        read_stdin(buffer, 10);
        base = strtol(buffer, NULL, 10);
    }

    do {
        printf("\n Veuillez entrer le nombres de valeurs:");
        read_stdin(buffer, 10);
        nbval = strtol(buffer, NULL, 10);
    } while (nbval <= 0);

    // Allocation des espaces mémoire nécessaires sur le tas :
    char **tab_chaine = (char **) malloc(nbval * sizeof(char *));
    for (int i = 0; i < nbval; i++) {
        // allocation pour 10 caractères + 1 caractère nul final
        tab_chaine[i] = (char *) malloc(11 * sizeof(char));
    }
    char *nombre_sortie;
    // Saisie des chaînes de caractères :
    for (int i = 0; i < nbval; i++) {
        // saisie d'une chaîne de 10 caractères maximum
        printf("\nNombre %d : ", i + 1);
        read_stdin(tab_chaine[i], 11);
        for (int j = 0; j < strlen(tab_chaine[i]); j++) {
            tab_chaine[i][j] = toupper(tab_chaine[i][j]);
        }
        nombre_sortie = baseToBase(tab_chaine[i], base, base);
        while (strcmp(tab_chaine[i], nombre_sortie) != 0) {
            printf("\nLe nombre entré n'est pas dans la base donnée\n");
            printf("\nNombre %d : ", i + 1);
            read_stdin(tab_chaine[i], 11);
            for (int j = 0; j < strlen(tab_chaine[i]); j++) {
                tab_chaine[i][j] = toupper(tab_chaine[i][j]);
            }
            nombre_sortie = baseToBase(tab_chaine[i], base, base);
        }
        free(nombre_sortie);
    }
    // Affichage des chaînes de caractères :
    show_string(nbval, tab_chaine);
    nbcaract = equalize(nbval, tab_chaine);

    //Creation de N seaux

    list_seau T[base];
    for (int i = 0; i < base; i++) {
        T[i].liste_chiffre = NULL;
    }
    int l, char_position;
    // On répète les étapes n fois, avec n le nombre de caractères du plus grand nombre
    for (int i = 0; i < nbcaract; i++) {
        // On place chaque nombre dans les seaux
        for (int j = 0; j < nbval; j++) {
            if (!isdigit(tab_chaine[j][nbcaract - char_position - 1])) {
                nombre_decimal = ctoi(tab_chaine[j][nbcaract - char_position - 1]);
            } else {
                nombre_decimal = tab_chaine[j][nbcaract - char_position - 1] - 48;
            }
            T[nombre_decimal].liste_chiffre = ajout_fin(T[nombre_decimal].liste_chiffre, tab_chaine[j]);
            tab_chaine[j][0] = '\0';
        }
        afficher_seaux(base, T);
        // On replace les nombres dans le tableau et on les retire des seaux
        l = 0;
        for (int k = 0; k < base; k++) {
            if (T[k].liste_chiffre != NULL) {
                List temp = T[k].liste_chiffre;
                while (temp != NULL) {
                    strcpy(tab_chaine[l], temp -> nombre);
                    l++;
                    temp = temp -> next;
                    T[k].liste_chiffre = supprimer_tete(T[k].liste_chiffre);
                }
            }
        }
        printf("\n");
        char_position++;
    }

    show_string(nbval, tab_chaine);

    // Libération des espaces alloués :
    for (int i = 0; i < nbval; i++) {
        free(tab_chaine[i]);
    }
    free(tab_chaine);
    return 0;
}