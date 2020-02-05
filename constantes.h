
#ifndef __CONSTANTES_H
#define __CONSTANTES_H



//Macros pour identifier:
#define line(x) (8 - ((x) / TAILLE_CASE))  //ligne
#define column(x) ((x) / TAILLE_CASE)      //colonne
#define areaL(x) (3 * ((x) / 3))           //la ligne de la région
#define areaC(x) (3 * ((x) / 3))           //la colonne de la région

//N: valeur pour les boucles - IMPOSSIBLE: valeur si case sans possibilité
#define N 9
#define IMPOSSIBLE -1

//Valeur des différents type de case
#define MODIFIABLE 15
#define NON_MODIFIABLE -15
#define AUTO 42


// Les tailles de case et de police sont prévues
// pour tout avoir proportionel, il suffit de changer la valeur de TAILLE_CASE
// et tout s'affiche en proportion
// A changer éventuellement
#define TAILLE_CASE 85 // La taille d'une case

#define LARGEUR (9*TAILLE_CASE+1)   // La taille horizontale de la fenêtre
#define HAUTEUR ((9+1)*TAILLE_CASE) // La taille verticale   de la fenêtre
#define TAILLE_POLICE ((2*TAILLE_CASE)/3)

// Les différentes couleurs à changer éventuellement
#define COUL_TITRE coral // Couleur du titre
#define COUL_FOND olivedrab  // Couleur de fond d'une case
#define COUL_FOND_PB rouge         // Couleur de fond d'un case qui ne peut plus prendre aucune valeur
#define COUL_TRAIT rosybrown        // Couleur des traits de séparation
#define COUL_ACCENTUE noir         // Couleur des traits de séparation accentués
#define COUL_VAL_DEPART darkred     // Couleur de la police des valeurs de départ
#define COUL_VAL_TRAVAIL vert    // Couleur de la police des valeurs de travail
#define COUL_VAL_AUTO goldenrod       // Couleur de la police des valeurs de résolution automatique

#endif
