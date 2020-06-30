/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			sauvegarde  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/


#ifndef __SAVE_H__
#define __SAVE_H__


#include <stdio.h>
#include "jeu.h"
#include "regle.h"

/* charge une partie déjà sauvegardée puis lance le jeu (en relançant chaque coup précédemment joué via le module règle.)*/
void charger_une_partie(CASE plateau[11][11], PILE* historique, JOUEUR* Joueur, CHOIX *choix, SDL_Surface ** fenetre, PIONS pion);

/* optionnel : affiche le plateau dans la console*/
void affiche_tab (CASE plateau[11][11]);

/* permet de sauvegarder une partie jouée : affiche le plateau dans un fichier ainsi que son  historique */
void sauvegarder_une_partie(PILE *historique, CASE plateau[11][11]);

/* met en application la fonction undo : retour en arrière : en mettant à jour l'historique, le tour du joueur et le plateau du jeu.*/
void option_reculer(PILE* historique, CASE plateau[11][11], JOUEUR *joueur, COO *coordonnees);

#endif
