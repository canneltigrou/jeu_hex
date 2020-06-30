
#ifndef __verif_H__
#define __verif_H__



#include <stdio.h>




typedef struct Pile_verif
{
	COO cases;
	CHOIX option;
	struct Pile_verif* suivant;
}*pile_verif;


COO depile_verif(pile_verif* ma_pile, CHOIX* option);

void empile_verif(pile_verif* ma_pile,CHOIX option, int x, int y);

int fonction_principale(pile_verif *ma_pile, int fonction);

void fonction1(void);

void fonction2(void);

void fonction4(void);



#endif
