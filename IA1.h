/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			Jeu  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/

#ifndef IA1_H
# define IA1_H
# include <stdio.h>
# include "jeu.h"


typedef struct cellule
{
	CASE couleur;
	int distance;
	COO previous;
}CELL;

void init_tab_IA(CELL tableau[11][11], CASE plateau[11][11]);


void propagation_2(CELL tableau[11][11],int compteur, int *touver,COO cases, PILE *list_cases);

COO depile(PILE* list);

void copier(CELL tab_min[11][11], CELL tableau[11][11]);

COO recherche_IA1(CASE plateau[11][11]);



#endif



