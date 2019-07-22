/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			detection_case  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/

#ifndef __detect_H__
#define __detect_H__

#include <stdio.h>
#include "jeu.h"

/* renvoie 1 si le clic n'est pas dans une des cases du plateau (les hexagones). sinon change les coordonnées de la cases du platau correpondante */
int determine_case_jeu (COO *cases, COO sdl_coo);

/* traite les clics dans le menu, et renvoie l'option choisie dans la variable choix*/
void detection_clic_menu (CHOIX * choix);

/* traite les clics sur les options lors d'un jeu en cours */
void detection_clic_jeu (CHOIX * choix, COO * cases);


#endif


