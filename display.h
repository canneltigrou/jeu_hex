/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			display  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/


#ifndef __display_H__
#define __display_H__


#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"
#include "detection_case.h"


#define WIDTH 850
#define HEIGHT 500

/* place en mémoire les différents SDL_Surfaces que utilisés tout au long du jeu*/
void init_fenetres (SDL_Surface **menu_window, SDL_Surface **board_window, PIONS * pions, sdlTOUR * tourjoueur, SDL_Surface **hist_window );

/* permet l'affichage soit du menu, soit du plateau*/
void maj_fenetre (SDL_Surface ** fenetre, SDL_Surface *a_mettre, Uint32 couleur);

/* affiche le dernier coup jouer à l'écran*/
void print_historique1 (SDL_Surface ** fenetre, PILE historique, SDL_Color couleurNoire, TTF_Font *police);

/*affichage dans une fenetre vierge des 12 derniers coups joués du plus récent au plus ancien */
void print_historique2 (PILE historique, SDL_Surface** fenetre, SDL_Surface *hist_window, SDL_Color couleurNoire, TTF_Font *police, Uint32 couleur );

/* affiche à qui appartient le tour de jouer */
void print_tour (SDL_Surface ** fenetre, sdlTOUR tourjoueur, JOUEUR joueur);

/* ajoute le pion au plateau. lors d'un undo, il permet aussi d'en enlever un*/
void ajout_pion (SDL_Surface ** fenetre,  PIONS pion, COO cases, JOUEUR joueur);

/* permet l'affichage de mon gagnant */
void print_gagnant(SDL_Surface **fenetre, JOUEUR gagnant, CHOIX *choix);

#endif





