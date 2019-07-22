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

#ifndef __JEU_H__
#define __JEU_H__


#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/* ce programme est la fonction main : il met en place les différentes variable et appelle les différentes fonctions des différents module au fil des besoin. */


typedef enum Case {vide, bleu, rouge, bleu_ch_G, bleu_ch_D, rouge_ch_H, rouge_ch_B }CASE;
typedef enum choix {jouer, lancer_partie_sauvegardee, IA1, IA2, quitter, sauvegarder, undo, reprendre, historique_aff} CHOIX;
typedef enum Joueur {jb, jr, personne} JOUEUR;
typedef struct coordonnee
{
	int x;
	int y;
}COO;



typedef struct pile
{
	int x;
	int y;
	JOUEUR joueur;
	struct pile * suivant;
} * PILE;

typedef struct pions
{
	SDL_Surface *pion_rouge;
	SDL_Surface *pion_bleu;
	SDL_Surface *pion_vide;
} PIONS;

typedef struct tourJoueur
{
	SDL_Surface *tour_rouge;
	SDL_Surface *tour_bleu;
} sdlTOUR;

void vider_historique(PILE* historique);

#endif





