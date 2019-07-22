CC = gcc
CFLAGS = -Wall -Werror # -ansi -pedantic -O2 -g
#gcc -Wall sdl.c -o sdl -lSDL -lSDL_image
INCLUDE = ./
OBJETS = jeu.o regle.o sauvegarde.o display.o detection_case.o IA1.o verif1.o
PROGRAMS = HEX

all: ${PROGRAMS}

regle.o: regle.c
	@echo
	@echo "################  regle.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} regle.c -c

sauvegarde.o: sauvegarde.c
	@echo
	@echo "################  sauvegarde.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} sauvegarde.c -c

jeu.o: jeu.c
	@echo
	@echo "################  jeu.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} jeu.c -c -lSDL -lSDL_image -lSDL_ttf


display.o: display.c
	@echo
	@echo "################  display.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} display.c -c -lSDL -lSDL_image -lSDL_ttf


detection_case.o: detection_case.c
	@echo
	@echo "################  detection_case.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} detection_case.c -c

IA1.o: IA1.c
	@echo
	@echo "################  IA1.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} IA1.c -c

verif1.o: verif1.c
	@echo
	@echo "################  verif1.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} verif1.c -c

main.o: main.c
	@echo
	@echo "################  main.o  ################"
	${CC} ${CFLAGS} -I${INCLUDE} main.c -c

HEX: jeu.o regle.o sauvegarde.o display.o detection_case.o IA1.o main.o
	@echo
	@echo "################  EDITION DES LIENS  ################"
	@echo "################  $@  ################"
	${CC} jeu.o regle.o sauvegarde.o display.o detection_case.o IA1.o main.o -o ${PROGRAMS} -lSDL -lSDL_image -lSDL_ttf

VERIF: verif1.o jeu.o regle.o sauvegarde.o display.o detection_case.o IA1.o
	@echo
	@echo "################  EDITION DES LIENS  ################"
	@echo "################  $@  ################"
	${CC} verif1.o jeu.o regle.o sauvegarde.o display.o detection_case.o IA1.o -o VERIF -lSDL -lSDL_image -lSDL_ttf

clean :
	rm -f  ${PROGRAMS} ${OBJETS} VERIF
re:
	make clean && make
	

