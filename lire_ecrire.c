#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uvsqgraphics.h>
#include "gestion_sudoku.h"
#include "constantes.h"

int convert_lire(int nb)
{
	switch (nb) {
	case '.':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	}
	return 0;
}

SUDOKU lire_fichier(char *nom)
{
	SUDOKU S;
	S.name = nom;
	FILE *fichier;

	fichier = fopen(nom, "r");
	if (fichier == NULL) {
		fprintf(stderr, "LIRE_FICHIER Open error\n");
		exit(-1);
	}

	else {
		int i, j;
		int charlu = fgetc(fichier);
		while (charlu != EOF) {
			for (i = 0; i < N; i++) {

				for (j = 0; j < N; j++) {
					if (charlu == '.') {
						S.cases[i][j].val = convert_lire('.');
						S.cases[i][j].type = MODIFIABLE;
					} 
					else if (charlu == '1') {
						S.cases[i][j].val = convert_lire('1');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '2') {
						S.cases[i][j].val = convert_lire('2');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '3') {
						S.cases[i][j].val = convert_lire('3');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '4') {
						S.cases[i][j].val = convert_lire('4');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '5') {
						S.cases[i][j].val = convert_lire('5');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '6') {
						S.cases[i][j].val = convert_lire('6');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '7') {
						S.cases[i][j].val = convert_lire('7');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '8') {
						S.cases[i][j].val = convert_lire('8');
						S.cases[i][j].type = NON_MODIFIABLE;
					} 
					else if (charlu == '9') {
						S.cases[i][j].val = convert_lire('9');
						S.cases[i][j].type = NON_MODIFIABLE;
					}
					//éviter d'avancer dans les colonnes du tableau quand retour à la ligne lu
					else if (charlu == '\n') {
						j = j - 1;
					} 
					else if (charlu == '*') {
						charlu = fgetc(fichier); //on veut decaler le curseur de lecture du fichier quand on lit '*'
						S.cases[i][j].type = MODIFIABLE;
						S.cases[i][j].val = convert_lire(charlu);
						if (charlu == '\n') {
							j = j - 1;
						}
					}
					charlu = fgetc(fichier);
				}

			}

		}

	}

	fclose(fichier);
	return S;
}


int convert_ecrire(int nb)
{
	switch (nb) {
	case 0:
		return 46;	//code ascii du point
	case 1:
		return 49;	//code ascii du 1
	case 2:
		return 50;	//code ascii du 2
	case 3:
		return 51;	//code ascii du 3
	case 4:
		return 52;	//code ascii du 4
	case 5:
		return 53;	//code ascii du 5
	case 6:
		return 54;	//code ascii du 6
	case 7:
		return 55;	//code ascii du 7
	case 8:
		return 56;	//code ascii du 8
	case 9:
		return 57;	//code ascii du 9
	}
	return 32;		//code ascii espace
}

int cpt = 0;
void ecrire_fichier(SUDOKU S)
{
	char s[20];
	cpt++;
	sprintf(s, "PLAY.%03d.sudoku", cpt);
	//~ sprintf(s, "PLAY1.%03d.sudoku", cpt);
	//~ sprintf(s, "PLAY2.%03d.sudoku", cpt);
	S.name = s;

	FILE *fichier = fopen(S.name, "w");
	if (fichier == NULL) {
		fprintf(stderr, "ECRIRE_FICHIER Open error\n");
		exit(-1);
	} else {
		int i, j;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (S.cases[i][j].type == MODIFIABLE && S.cases[i][j].val != 0) {
					fputc('*', fichier);
					fputc(convert_ecrire(S.cases[i][j].val), fichier);
				} else {
					fputc(convert_ecrire(S.cases[i][j].val), fichier);
				}
			}
			fputc('\n', fichier);
		}
	}
	fclose(fichier);

}
