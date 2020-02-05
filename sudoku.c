#include <stdlib.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "afficher.h"
#include "gestion_sudoku.h"
#include "lire_ecrire.h"

SUDOKU jouer(SUDOKU S, Pile ** p)
{
	Liste *l = NULL;
	char t;
	int f;
	POINT centre;
	int code = wait_key_arrow_clic(&t, &f, &centre);
	if (code == EST_TOUCHE) {
		if (t == 'U') {
			printf("\n");
			printf("ENTREE de UNDO\n");
			int ligne = Ligne(p);
			int colonne = Colonne(p);
			int valeur = Valeur(p);
			//~ printf("ELEMENT DEPILER : %d %d %d\n",ligne,colonne,valeur);
			depiler(p);
			//~ afficherPile(p);
			if (ligne == -1) {
				return S;
			}
			S = undo_modif(S, ligne, colonne, valeur);
			printf("SORTIE de UNDO\n");
			return S;
		} else if (t == 'V') {
			int i, j;
			int x;
			for (x = 0; x < 81; x++) {
				l = liste_possibilite(S);
				if (case_libre(S, &i, &j)) {
					S = resoudre(resoudre(S, l), l);
					l = l->suivant;
				}
			}
			if (case_libre(S, &i, &j) == 1) {
				sudoku_afficher(S);
				wait_escape();
				message_erreur();
				terminer_fenetre_graphique();
				return S;
			}
			free(l);
			return S;

		} else if (t == 'S') {
			ecrire_fichier(S);
		} else if (t == 'Q') {
			ViderPile(p);
			terminer_fenetre_graphique();
		}
	} else if (code == EST_CLIC) {
		printf("ENTREE DE sudoku_modifier_case\n");
		empiler(p, line(centre.y), column(centre.x),
			S.cases[line(centre.y)][column(centre.x)].val);
		S = sudoku_modifier_case(S, centre.x, centre.y);
		//~ afficherPile(p);
	}
	return S;
}

int main(int argc, char *argv[])
{
	SUDOKU S;
	Pile *p = NULL;
	S = lire_fichier(argv[1]);
	initialiser_fenetre_graphique();
	sudoku_afficher(S);
	affiche_auto_off();
	int i, j;
	do {
		S = jouer(S, &p);
		sudoku_afficher(S);
		case_libre(S, &i, &j);
		affiche_all();
	} while (case_libre(S, &i, &j) != 0);

	sudoku_afficher(S);
	terminer_fenetre_graphique();
	resultat_sudoku();
	free(p);
	exit(0);
}
