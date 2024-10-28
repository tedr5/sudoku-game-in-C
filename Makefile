CFLAGS = -g -Wall -c
CFLAGSGR = ${CFLAGS} `sdl-config --cflags`
LFLAGS = -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf


run: sudoku
#valgrind --leak-check=full ./sudoku PLAY.000.sudoku
	./sudoku PLAY.000.sudoku
#./sudoku PLAY.001.sudoku
#./sudoku PLAY.002.sudoku
#./sudoku PLAY1.000.sudoku
#./sudoku PLAY2.000.sudoku

# Edition de lien du programme principal
sudoku: sudoku.o afficher.o gestion_sudoku.o lire_ecrire.o 
	gcc -o $@ $^ ${LFLAGS}

# Compilation du programme principal
sudoku.o: sudoku.c lire_ecrire.h gestion_sudoku.h constantes.h
	gcc ${CFLAGSGR} $*.c

# Compilation des différents.o
afficher.o: afficher.c afficher.h gestion_sudoku.h constantes.h
	gcc ${CFLAGSGR} $*.c

gestion_sudoku.o: gestion_sudoku.c gestion_sudoku.h
	gcc ${CFLAGSGR} $*.c

lire_ecrire.o: lire_ecrire.c lire_ecrire.h gestion_sudoku.h
	gcc ${CFLAGSGR} $*.c


indent:
	indent -linux *.c

editeur:
	geany  Makefile *.c *.h *.sudoku *.txt &

# Le clean
clean:
	rm -f *.o
	rm -f sudoku
	rm -f Aide.txt



# Pour faire un zip
# Mettre son nom à la place de SUDOKU
LENOM=MY_NAME
zip:
	rm -rf ${LENOM}
	rm -rf ${LENOM}.zip
	mkdir ${LENOM}
	cp Makefile ${LENOM}
	cp *.h *.c ${LENOM}
	cp A_LIRE.txt ${LENOM}
	zip -r ${LENOM}.zip ${LENOM}
	rm -rf ${LENOM}
