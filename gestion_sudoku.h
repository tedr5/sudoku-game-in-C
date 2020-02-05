
#ifndef __SUDOKU_H
#define __SUDOKU_H
#include "constantes.h"
struct one_case{
   int val;  // Valeur de la case allant de 1 a 9
   int type; // Modifiable - Non modifiable 
}; 
struct sudoku {
char *name; //Nom du fichier .sudoku
struct one_case cases[N][N];//Tableau que l'on manipule
};
typedef struct sudoku SUDOKU;

////////////////////////////////////////////////////////
typedef struct pile{  //La pile afin de faire le undo
  int Ligne;  
  int Colonne; 
  int Valeur;
  struct pile* precedent;
}Pile;

void afficherPile(Pile **p); //Afficher la pile

void empiler(Pile **p,int li,int col,int val); //Empiler un element au sommet de la pile

void depiler(Pile **p); //Depiler l'element du sommet

void ViderPile(Pile **p); //Vider la pile quand fini de jouer

int Ligne(Pile **p);  //Récupérer le champ Ligne de l'élément au sommet de la pile

int Colonne(Pile **p); //Récupérer le champ Colonne de l'élément au sommet de la pile

int Valeur(Pile **p);  //Récupérer le champ Valeur de l'élément au sommet de la pile

SUDOKU auxiliaire(SUDOKU S,int i,int j); // Mettre dans un fichier "Aide.txt" la ligne-colonne-valeur des cases cliquées
/////////////////////////////////////////////////////////////////
typedef struct liste{    //Liste afin de trouver une solution au sudoku
  int ligne;
  int colonne;
  int nb_possibilite;
   struct liste *suivant;	
}Liste;

void afficher_liste(Liste *l); //Afficher la liste

Liste *creer_element(Liste *l,int lg,int col,int nb_poss); //Cree un element

Liste *inserer_trie(Liste *l,int lg,int col,int nb_poss); //Insère dans la liste l'élément par valeur croissante du nombre de possibilité

Liste* liste_possibilite(SUDOKU S); //Cree la liste des cases vides,avec leur ligne,colonne et le nombre de valeurs possibles de celles ci

//////////////////////////////////////////////////////
int ValeurValide(SUDOKU S, int val,int i,int j); //Retourne une valeur possible a mettre dans la case

int ValeurValide2(SUDOKU S, int val, int i, int j); //Retourne une valeur possible pour la resolution automatique

SUDOKU sudoku_modifier_case(SUDOKU S,int i,int j); //Modifie le contenu de cette case si c’est une case 
                                                   //de travail en lui mettant la prochaine valeur disponible

SUDOKU undo_modif(SUDOKU S, int i, int j,int val); //Modifie la case pour le undo

int case_libre(SUDOKU S,int *lg,int *col); //Chercher si encore des cases disponibles
                                                         
SUDOKU resoudre(SUDOKU S,Liste *l); // Résoudre automatiquement le sudoku


#endif
