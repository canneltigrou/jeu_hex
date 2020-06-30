/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			regle  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/

#ifndef __REGLE_H__
#define __REGLE_H__


#include <stdio.h>
#include "jeu.h"


/* si un pion est noté comme relié à une bordure qui lui correspond (de manière directe ou indirecte) il propage sa nouvelle identité (exemple en tant que 'marqué comme touchant le bord droit' (bleu_ch_D))*/
void propagation(CASE plateau[11][11], COO cases, CASE couleur, CASE a_remplacer);

/* empile la pile historique :ajoute le dernier coup joué à l'historique.*/
void empile (PILE* historique, COO coordonnees, JOUEUR joueur);


/* il prend en entré la case cliquée, le plateau. Il vérifie si la case est jouable (ie si elle est vide). si oui, il met à jour le plateau, le tour du joueur, l'historique. Il vérifie si le coup est gagnant : si oui, il met à jour la variable gagnant.*/
int regle(CASE plateau[11][11], COO cases, JOUEUR * gagnant, JOUEUR * joueur, PILE *historique);

#endif
