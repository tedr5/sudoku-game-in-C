#include <stdio.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "gestion_sudoku.h"

void afficher_titre(char *titre)
{
	POINT nom;
	nom.x = LARGEUR / 10;
	nom.y = TAILLE_CASE * 10;
	aff_pol(titre, TAILLE_POLICE, nom, COUL_TITRE);

}

void afficher_grille()
{
	POINT p1, p2;
	p1.x = 0;
	p1.y = HAUTEUR - TAILLE_CASE;
	p2.x = p1.x;
	p2.y = 0;

	while (p1.x <= LARGEUR) {	//VERTICALES
		if (p1.x == 0 || p1.x == 3 * TAILLE_CASE
		    || p1.x == 6 * TAILLE_CASE || p1.x == 9 * TAILLE_CASE) {
			draw_line(p1, p2, COUL_ACCENTUE);
			p1.x = p1.x + TAILLE_CASE;
			p2.x = p1.x;
		} else {
			draw_line(p1, p2, COUL_TRAIT);
			p1.x = p1.x + TAILLE_CASE;
			p2.x = p1.x;
		}
	}
	POINT p3, p4;
	p3.x = 0;
	p3.y = 0;
	p4.x = LARGEUR;
	p4.y = 0;
	while (p3.y <= HAUTEUR) {	//HORIZONTALES
		if (p3.y == 0 || p3.y == 3 * TAILLE_CASE
		    || p3.y == 6 * TAILLE_CASE || p3.y == 9 * TAILLE_CASE) {
			draw_line(p3, p4, COUL_ACCENTUE);
			p3.y = p3.y + TAILLE_CASE;
			p4.y = p3.y;
		} else {
			draw_line(p3, p4, COUL_TRAIT);
			p3.y = p3.y + TAILLE_CASE;
			p4.y = p3.y;
		}

	}
}

void afficher_rectangle(int i, int j)
{

	POINT bg, hd;
	bg.x = ((j * TAILLE_CASE) + 1);
	bg.y = (9 - i - 1) * TAILLE_CASE + 1;
	hd.x = (bg.x - 1 + TAILLE_CASE) - 1;
	hd.y = (bg.y - 1 + TAILLE_CASE) - 1;
	draw_fill_rectangle(bg, hd, COUL_FOND_PB);
}

char *format(int nb)
{
	switch (nb) {
	case 0:
		return " ";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	}
	return " ";
}

void valeur(SUDOKU S, int i, int j)
{
	POINT p;
	p.x = j * (TAILLE_CASE) + TAILLE_CASE / 3;
	p.y = (9 - i) * (TAILLE_CASE);

	if (S.cases[i][j].val == IMPOSSIBLE) {
		afficher_rectangle(i, j);
	}
	if (S.cases[i][j].type == NON_MODIFIABLE) {
		aff_pol(format(S.cases[i][j].val), TAILLE_POLICE, p,
			COUL_VAL_DEPART);

	} else if (S.cases[i][j].type == MODIFIABLE) {

		aff_pol(format(S.cases[i][j].val), TAILLE_POLICE, p,
			COUL_VAL_TRAVAIL);
	} else if (S.cases[i][j].type == AUTO) {
		aff_pol(format(S.cases[i][j].val), TAILLE_POLICE, p,
			COUL_VAL_AUTO);
	}
}

void initialiser_fenetre_graphique()
{
	init_graphics(LARGEUR, HAUTEUR);
}

void terminer_fenetre_graphique()
{
	wait_escape();
}

void sudoku_afficher(SUDOKU S)
{
	fill_screen(COUL_FOND);
	afficher_titre(S.name);
	afficher_grille();
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			valeur(S, i, j);
		}
	}

}

void resultat_sudoku()
{
	initialiser_fenetre_graphique();
	fill_screen(COUL_FOND);
	char s[6];
	sprintf(s, "GAGN\xc9");
	POINT p;
	p.x = 3 * TAILLE_CASE;
	p.y = HAUTEUR / 2;
	aff_pol(s, TAILLE_CASE, p, rouge);
	terminer_fenetre_graphique();
}

void message_erreur()
{
	initialiser_fenetre_graphique();
	fill_screen(rouge);
	char s[7];
	char s2[11];
	char s3[15];
	sprintf(s, "ERREUR");
	sprintf(s2, "RESOLUTION");
	sprintf(s3, "AUTOMATIQUE");
	POINT p1, p2, p3;
	p1.x = LARGEUR / TAILLE_CASE * 2;
	p1.y = HAUTEUR - TAILLE_CASE * 4;
	p2.x = LARGEUR / TAILLE_CASE * 2;
	p2.y = HAUTEUR - TAILLE_CASE * 5;
	p3.x = LARGEUR / TAILLE_CASE * 2;
	p3.y = HAUTEUR - TAILLE_CASE * 6;
	aff_pol(s, TAILLE_CASE, p1, noir);
	aff_pol(s2, TAILLE_CASE, p2, noir);
	aff_pol(s3, TAILLE_CASE, p3, noir);
	terminer_fenetre_graphique();

}
