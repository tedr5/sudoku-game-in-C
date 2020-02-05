
#ifndef __LIRE_ECRIRE_H
#define __LIRE_ECRIRE_H

int convert_lire(int nb);// Utile pour la fonction lire fichier. En fonction du caractere, on retourne sa valeur en entier à mettre dans le tableau


SUDOKU lire_fichier (char *nom);// Lecture d'un fichier .sudoku


int convert_ecrire(int nb);//Utile pour la fonction ecrire fichier. En fonction du nombre entier , on retourne la valeur de son code ASCII pour fputc


void ecrire_fichier(SUDOKU S);// Ecriture d'un sudoku dans un fichier
#endif
