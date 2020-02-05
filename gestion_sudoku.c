#include <stdlib.h>
#include <uvsqgraphics.h>
#include "gestion_sudoku.h"
#include "afficher.h"
#include "constantes.h"
#include "lire_ecrire.h"

void afficherPile(Pile ** p)
{
	Pile *voir = *p;	// on cree un pointeur qui va nous permettre de parcourir la pile
	while (voir != NULL) {
		printf("%d %d %d\n", voir->Ligne, voir->Colonne, voir->Valeur);
		voir = voir->precedent;
	}
	free(voir);
}

void empiler(Pile ** p, int li, int col, int val)
{
	Pile *nouveau = malloc(sizeof *nouveau);
	if (nouveau != NULL) {
		nouveau->Ligne = li;
		nouveau->Colonne = col;
		nouveau->Valeur = val;
		nouveau->precedent = *p;	//on fait pointer l'element cree sur le sommet de la pile
		*p = nouveau;	//on fait pointer le sommet de la pile sur ce nouvel element
	}
}

void depiler(Pile ** p)
{
	if (*p != NULL)		// si la pile nest pas un pointeur null
	{
		Pile *tmp = (*p)->precedent;	// on stocke l'avant dernier element de la pile
		free(*p);	// on supprime le dernier element
		*p = tmp;	//apres avoir supprimer le dernier element, on fait pointer la pile sur l'avant dernier element 
	}
}

void ViderPile(Pile ** p)
{
	while (*p != NULL) {
		depiler(p);
	}
}

int Ligne(Pile ** p)
{
	int lg = -1;		//sert quand la pile est vide
	if (*p != NULL) {
		lg = (*p)->Ligne;
	}
	return lg;
}

int Colonne(Pile ** p)
{
	int colonne = -1;	//sert quand la pile est vide
	if (*p != NULL) {
		colonne = (*p)->Colonne;
	}
	return colonne;
}

int Valeur(Pile ** p)
{
	int valeur = -1;	//sert quand la pile est vide
	if (*p != NULL) {
		valeur = (*p)->Valeur;
	}
	return valeur;
}

//Fonction qui va nous mettre dans un fichier temporaire les coordonnees des cases, et leur valeur:
//Format: Ligne Colonne Valeur.
SUDOKU auxiliaire(SUDOKU S, int i, int j)
{
	FILE *f = fopen("Aide.txt", "a");
	if (f == NULL) {
		printf("OPEN ERROR auxiliaire\n");
		exit(-1);
	} else {
		int k = S.cases[i][j].val;
		fprintf(f, "%d ", i);
		fprintf(f, "%d ", j);
		fprintf(f, "%d\n", k);
	}
	fclose(f);
	return S;
}

///////////////////////////////////////////////////////////////////////
void afficher_liste(Liste * l)
{
	if (l) {
		printf("#%d", l->ligne);
		printf(" %d ", l->colonne);
		printf("%d# ", l->nb_possibilite);
		afficher_liste(l->suivant);
	} else
		printf("\n");
}

Liste *creer_element(Liste * l, int lg, int col, int nb_poss)
{
	Liste *tmp;
	tmp = malloc(sizeof(Liste *));
	if (!tmp) {
		fprintf(stderr, "Cannot malloc\n");
		exit(-1);
	}
	tmp->ligne = lg;
	tmp->colonne = col;
	tmp->nb_possibilite = nb_poss;
	tmp->suivant = l;
	return tmp;
}

Liste *inserer_trie(Liste * l, int lg, int col, int nb_poss)
{
	if ((!l) || (nb_poss <= l->nb_possibilite))
		return creer_element(l, lg, col, nb_poss);
	l->suivant = inserer_trie(l->suivant, lg, col, nb_poss);
	return l;
}

Liste *liste_possibilite(SUDOKU S)	
{
	Liste *l = NULL;
	int i, j, x;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			int cpt = 0;
			if (S.cases[i][j].val == 0
			    && S.cases[i][j].type == MODIFIABLE) {
				for (x = 0; x < 10; x++) {
					if (ValeurValide2(S, x, i, j)) {
						cpt++;
					}
				}
				if (cpt != 0) {
					l = inserer_trie(l, i, j, cpt);
					afficher_liste(l);
				}
				printf("\n");
			}
		}
	}
	return l;
}

///////////////////////////////////////////////////////////////////////
// Renvoi 1 quand conditions ligne i, colonne j, region satisfaites
//Val est la valeur a tester
int ValeurValide(SUDOKU S, int val, int i, int j)
{
	int x, y;
	int lg = line(j), col = column(i);
	int regionL = areaL(lg), regionC = areaC(col);
	for (x = 0; x < N; x++) {
		if (x != col) {
			if (S.cases[lg][x].val == val) {
				return 0;
			}
		}
	}

	for (x = 0; x < N; x++) {
		if (x != lg) {
			if (S.cases[x][col].val == val) {
				return 0;
			}
		}
	}
	for (x = regionL; x < regionL + 3; x++) {
		for (y = regionC; y < regionC + 3; y++) {
			if ((x != lg) && (y != col)) {
				if (S.cases[x][y].val == val) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int ValeurValide2(SUDOKU S, int val, int i, int j)
{
	int x, y;
	int regionL, regionC;
	for (x = 0; x < N; x++) {
		if (x != j) {
			if (S.cases[i][x].val == val) {
				return 0;
			}
		}
	}

	for (x = 0; x < N; x++) {
		if (x != i) {
			if (S.cases[x][j].val == val) {
				return 0;
			}
		}
	}
	regionL = areaL(i);
	regionC = areaC(j);
	for (x = regionL; x < regionL + 3; x++) {
		for (y = regionC; y < regionC + 3; y++) {
			if ((x != i) && (y != j)) {
				if (S.cases[x][y].val == val) {
					return 0;
				}
			}
		}
	}
	return 1;
}

SUDOKU sudoku_modifier_case(SUDOKU S, int i, int j)	//Modifier contenu de la case,si case de travail
{
	int lg = line(j), col = column(i);
	int x, n;
	int possible[10];
	int cpt = 0;

	if (S.cases[lg][col].type == MODIFIABLE) {
		// ON REMPLIT LE TAB DES 10 POSSIBILITES, indicé de 0 a 9
		for (n = 0; n < 10; n++) {
			possible[n] = 0;
		}
		// SI LA VALEUR X EST POSSIBLE ALORS ON MET 1
		for (x = 0; x < 10; x++) {
			if (ValeurValide(S, x, i, j)) {
				possible[x] = 1;
				cpt++;
			}
			//~ printf(" %d ", possible[x]);
		}
		//~ printf("\n");

		int courant = S.cases[lg][col].val;
		for (n = 0; n < 10; n++) {
			courant = courant + 1;
			if (courant == 10 || S.cases[lg][col].val == IMPOSSIBLE) {
				courant = 0;
				S.cases[lg][col].val = 0;
				//~ S = auxiliaire(S,lg,col);
				return S;
			} else if (possible[courant] == 1) {
				S.cases[lg][col].val = courant;
				//~ S = auxiliaire(S, lg, col);
				return S;
			} else if (cpt == 0) {
				S.cases[lg][col].val = IMPOSSIBLE;
				//~ S = auxiliaire(S, lg, col);
				return S;
			}
		}
	}
	printf("SORTIE DE sudoku_modifier_case\n");
	return S;
}

SUDOKU undo_modif(SUDOKU S, int i, int j, int val)	//Modifier contenu de la case avec le Undo
{
	S.cases[i][j].val = val;
	return S;
}

SUDOKU sudoku_modifier_case2(SUDOKU S, int i, int j)	//Modifier contenu de la case avec la résolution automatique
{
	int n;
	for (n = 0; n <= N; n++) {
		if (ValeurValide2(S, n, i, j)) {
			S.cases[i][j].type = AUTO;
			S.cases[i][j].val = n;
		}
	}
	return S;
}

int case_libre(SUDOKU S, int *lg, int *col)	//trouver la ligne et colonne de la prochaine case vide, renvoi 1 quand encore des cases vides sinon 0
{
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (S.cases[i][j].val == 0) {
				*lg = i;
				*col = j;
				return 1;

			}
		}
	}
	return 0;

}

SUDOKU resoudre(SUDOKU S, Liste * l) //resoudre le sudoku en fonction de l'état courant du sudoku
{
	if (l == NULL) {
		printf("LISTE VIDE\n");
		sudoku_afficher(S);
		wait_escape();
		message_erreur();
		wait_escape();
		exit(1);
	}

	int lg = l->ligne, col = l->colonne;
	S = sudoku_modifier_case2(S, lg, col);

	printf("FIN resoudre\n");

	return S;
}
