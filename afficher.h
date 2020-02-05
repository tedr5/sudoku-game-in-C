#include "gestion_sudoku.h"
#ifndef __AFFICHER_H
#define __AFFICHER_H


void afficher_titre(char *titre);//Afficher le nom du sudoku

void afficher_grille();//Afficher le quadrillage

void afficher_rectangle(int i,int j);//Afficher rectangle à la ligne i colonne j si aucune valeur possible dans la case

char* format(int nb);//Transforme la valeur int pour l'affichage avec affpol

void valeur(SUDOKU S,int i, int j);// Affiche le chiffre correspondant à la ligne i,colonne j. Sinon affiche le rectangle 

void initialiser_fenetre_graphique();// Fonction à appeler au début poour créer la fenêtre grapĥique

void terminer_fenetre_graphique();// Fonction a appeler à la fin pour terminer proprement la fenêtre grapĥique

void sudoku_afficher(SUDOKU S);//Fonction qui affiche l'etat courant du sudoku

void resultat_sudoku();//Afficher "Gagné" si on a fini le sudoku

void message_erreur();//Aficher une erreur si problème pour trouver une solution


#endif
