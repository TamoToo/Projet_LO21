#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "main_functions.h"

void show_string(int nbval, char ** tableau) {
    for (int i = 0; i < nbval; i++) {
        printf("Nombre %d :  ", i + 1);
        printf("'%s'\n", tableau[i]);
    }
}

void reverse_string(char * string) {
    char temp;
    for (int i = 0; i < strlen(string) / 2; i++) {
        temp = string[i];
        string[i] = string[strlen(string) - i - 1];
        string[strlen(string) - i - 1] = temp;
    }
}

int ctoi(char caractere) {
    int nombre;
    switch (caractere) {
    case 'A':
        nombre = 10;
        break;
    case 'B':
        nombre = 11;
        break;
    case 'C':
        nombre = 12;
        break;
    case 'D':
        nombre = 13;
        break;
    case 'E':
        nombre = 14;
        break;
    default:
        nombre = 15;
        break;
    }
    return nombre;
}

char itoc(int nombre) {
    char caractere;
    switch (nombre) {
    case 10:
        caractere = 'A';
        break;
    case 11:
        caractere = 'B';
        break;
    case 12:
        caractere = 'C';
        break;
    case 13:
        caractere = 'D';
        break;
    case 14:
        caractere = 'E';
        break;
    default:
        caractere = 'F';
        break;
    }
    return caractere;
}

char * baseToBase(char * nombre_entree, int base_entree, int base_sortie) {
    // On va passer par la représentation décimale pour faire la conversion
    int j = 0;
    int nb_zero;
    long int nombre_decimal = 0;
    int taille_nombre = strlen(nombre_entree);
    int power = taille_nombre;

    int max_power = 0;
    long int quotient, reste;
    char * nombre_sortie = (char * ) calloc(11, sizeof(char));
    // Conversion vers la base 10
    for (int i = 0; i < taille_nombre; i++, power--) {
        if (!isdigit(nombre_entree[i])) {
            nombre_decimal += ctoi(nombre_entree[i]) * pow(base_entree, power - 1);
        } else {
            nombre_decimal += (nombre_entree[i] - '0') * pow(base_entree, power - 1);
        }
    }

    // Conversion vers la base n
    while (pow(base_sortie, max_power) <= nombre_decimal) {
        max_power++;
    }
    quotient = nombre_decimal;
    for (int i = 0; i < max_power; i++) {
        reste = quotient % base_sortie;
        quotient /= base_sortie;
        if (reste > 9) {
            nombre_sortie[i] = itoc(reste);
        } else {
            nombre_sortie[i] = reste + '0';
        }
    }
    while (nombre_entree[j] == '0') {
        strcat(nombre_sortie, "0");
        j++;
    }
    reverse_string(nombre_sortie);
    return nombre_sortie;
}

//Afin d'avoir des chaines de caractères de même taille
int equalize(int nbval, char ** tableau) {
    int max = 0;
    int nbchar, nbgap; // nbchar : nombre de caractère d'un nombre, nbgap : différence entre le max et nbchar
    //ON cherche le nombre avec le plus de caractères
    for (int i = 0; i < nbval; i++) {
        nbchar = strlen(tableau[i]);
        if (nbchar > max) {
            max = nbchar;
        }
    }
    // Pour chaque mot on va vérifier si le nombre de caractère est différent du nbcaracmax pour rajouter des 0
    for (int j = 0; j < nbval; j++) {
        nbchar = strlen(tableau[j]);
        if (nbchar != max) {
            nbgap = max - nbchar;
            for (int k = nbchar - 1; k >= 0; k--) {
                tableau[j][k + nbgap] = tableau[j][k];
            }
            for (int l = 0; l < nbgap; l++) {
                tableau[j][l] = '0';
            }
        }
    }
    return max;
}

void afficher_seaux(int base, list_seau T[]) {
    for (int i = 0; i < base; i++) {
        if (i > 9) {
            T[i].num[1] = itoc(i);
        } else {
            T[i].num[1] = i + '0';
        }
        afficher_list(T[i].liste_chiffre, T[i].num[1]);
    }
}

void afficher_list(List l, char numero_seau) {
    if (l == NULL) {
        /*printf("la liste est vide\n");*/
    } else {
        printf("\nSeau %c: ", numero_seau);
        List tmp = l;
        while (tmp -> next != NULL) {
            printf("%s ", tmp -> nombre);
            tmp = tmp -> next;
        }
        printf("%s ", tmp -> nombre);
    }
}

List ajout_fin(List l, char * c) {
    List new_nbr = (seau * ) malloc(sizeof(seau));
    new_nbr -> nombre = (char * ) malloc(11 * sizeof(char));
    strcpy(new_nbr -> nombre, c);

    new_nbr -> next = NULL;

    if (l == NULL) {
        return new_nbr;
    } else {
        List temp = l;
        while (temp -> next != NULL) {
            temp = temp -> next;
        }
        temp -> next = new_nbr;
        return l;
    }
}

List supprimer_tete(List l) {
    if (l == NULL) {
        return NULL;
    } else {
        List aRenvoyer = l -> next;
        free(l -> nombre);
        free(l);
        return aRenvoyer;
    }
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int read_stdin(char * chaine, int longueur) {
    char * positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            * positionEntree = '\0';
        } else {
            viderBuffer();
        }
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}