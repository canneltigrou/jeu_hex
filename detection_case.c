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




#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "detection_case.h"
#include "jeu.h"



/* prenons pour référence la 1ere case en haut à gauche */
/* PROBLEME  : les coordonnées de sdl se basent en haut à gauche. je dois donc échanger le sens de l'axe. */


/* construisons immaginairement des rectangles avec pour 
- coin en bas à gauche du rectangle le coin bas gauche de l'hexagone;
- coin en bas à droite du rectangle le coin bas droite de l'hexagone;
- le coté haut du rectangle passe par le sommet nord de l'hexagone;*/

int determine_case_jeu(COO *cases, COO sdl_coo)
{
	int i;
	int j;
	int i_debut;
	int b;
	float pente_HD; /* correspondant à la pente du coté bas_droite de l'hexagone */
	float pente_HG; /* - - - - - - - - - - - - - - coté gas gauche  - - - - - - -*/
	
	/* je définis les coordonnées de 4 points principaux utilisés */
	COO rectangle_HG; /* coin haut-gauche du 1er rectangle en bas à gauche*/
	COO rectangle_BG; /* coin bas-gauche du 1er rectangle en bas à gauche */
	COO hexagone_H; /* sommet sud de l'hexagone en bas à gauche (ie milieu du coté bas du rectangle*/
	COO hexagone_HG; /* sommet bas-gauche de l'hexagone */
	
	rectangle_HG.x = 399; 
	rectangle_HG.y = 52;
	rectangle_BG.x = 399;
	rectangle_BG.y = 83;
	hexagone_H.x = 417;
	hexagone_H.y = 52;
	hexagone_HG.x = 399;
	hexagone_HG.y = 63;
	
	pente_HG = (float)(hexagone_H.y - hexagone_HG.y)/(float)(hexagone_H.x - hexagone_HG.x);
	
	pente_HD = (-1) * pente_HG;
	
	/* je regarde dans quelle ligne je me situe. ie, je regarde selon l'intervalle des y.*/
	if (sdl_coo.y < rectangle_HG.y)
		return(1); /* je suis au dessus de la grille*/
	
	j = 0;
	while ( j<12 && (sdl_coo.y > rectangle_BG.y - j*(rectangle_HG.y - rectangle_BG.y) ))
		j++;
	
	if (j == 12)
		return(1); /* je suis en-dessous de la grille */
		
	/* cherchons maintenant dans quelle colonne */
	/* définissons les x des la 1ere case en fonction du y trouvé (ie i_debut = f(j) ) */
	i_debut = rectangle_HG.x - j*(hexagone_H.x - rectangle_HG.x);
	
	if (sdl_coo.x < i_debut)
		return(1); /* je suis trop à gauche */
	
	i=0;
	while ( i<12 && (sdl_coo.x > (i_debut + i*2*(hexagone_H.x - rectangle_HG.x))))
		i++;
	i--;	

	if (i == 12)
		return (1); /* je suis trop à droite */
	
	
	
	
	/* reste à savoir si je suis réellement dans l'hexagone de ces coordonnées, ou bien dans un bord d'un des 2 hexagones en dessous. */
	/* pour cela, comparons avec les droites formant les cotés bas de l'haxagone se situant dans ce rectangle */
	
	/* calculons l'ordonnée à l'origine (b) de l'equation de la droite du coté gauche haut de l'hexagone : pour cela, basons nous sur le bas de l'hexagone du rectangle où nous nous trouvons. */
	
	b = (rectangle_HG.y + j*(rectangle_BG.y - rectangle_HG.y)) ;
	b= b- (pente_HG * (i_debut + (i*2+1) *(hexagone_H.x - hexagone_HG.x)));
	
	if (sdl_coo.y < (pente_HG * sdl_coo.x + b))
	{ /* sauf extrémité, je me trouve dans le triangle droit de l'hexgone du dessus*/
		if(j<1 || i<1)
			return(1); /* je suis trop haut */
		else
		{
			cases->x = i-1; 
			cases->y = 10 - (j-1);/* je le remets dans le bon sens de mon plateau*/
			return(0);
		}
	}
	
	b = (rectangle_HG.y + j*(rectangle_BG.y - rectangle_HG.y)) ;
	b= b - (pente_HD * (i_debut + (i*2+1) * (hexagone_H.x - hexagone_HG.x)));
	
	if (sdl_coo.y < (pente_HD *sdl_coo.x + b))
	{
		if (j<1 || i>10)
			return(1);
		else
		{
			cases->x = i;
			cases->y = 10 - (j-1);
			return(0);
		}
	}
	else
	{
		if (j>10 || i>10)
			return(1);
		else
		{
			cases->x = i;
			cases->y = 10 -j;
			return(0);
		}
	}
}
	
void detection_clic_jeu (CHOIX * choix, COO * cases)
{
	SDL_Event event;
	int probleme = 1; /* 1 si problème. problème tant qu'aucun bouton n'a été sélevtionné.*/
	
	while(probleme)
	{
		SDL_WaitEvent(&event);
		
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			/* clic sur Undo ? */
			if ( 54 < event.button.x && event.button.x < 126  &&   249 < event.button.y && event.button.y < 282  )
			{
				*choix = undo;
				probleme = 0;
			}
			
			/* clic sur sauvegarder ? */
			if ( 54 < event.button.x && event.button.x < 193 &&   297 < event.button.y && event.button.y < 346  )
			{
				*choix = sauvegarder;
				probleme = 0;
			}
		
			/* clic sur quitter*/
			if (54 < event.button.x && event.button.x < 127 && 367 < event.button.y && event.button.y < 400 )
			{
				*choix = reprendre;
				probleme = 0;
			}
			
			/* clic sur historique*/
			if (659 < event.button.x && event.button.x < 821 && 353 < event.button.y && event.button.y < 397 )
			{
				*choix = historique_aff;
				probleme = 0;
			}
			
			/* clic sur un hexagone ?*/
			if(probleme)
			{
				COO sdl_coo;
				sdl_coo.x = event.button.x;
				sdl_coo.y = event.button.y;
				probleme = determine_case_jeu(cases, sdl_coo);
			}
			
		}
		else
			if (event.type == SDL_QUIT)
				{
				*choix = quitter;
				probleme = 0;
				}
	}
}

void detection_clic_menu (CHOIX * choix)
{
	SDL_Event event;
	int probleme = 1; /* 1 si problème. problème tant qu'aucun bouton n'a été sélevtionné.*/
	
	while(probleme)
	{
		SDL_WaitEvent(&event);
			
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			/* clic sur Joueur Vs Joueur ? */
			if ( 295 < event.button.x && event.button.x < 607  &&   45 < event.button.y && event.button.y < 112  )
			{
				*choix = jouer;
				probleme = 0;
			}
			
			/* clic sur Joueur Vs IA ? */
			if ( 295 < event.button.x && event.button.x < 607 &&   133 < event.button.y && event.button.y < 200  )
			{
				*choix = IA1;
				probleme = 0;
			}
			
			/* clic sur Reprendre une partie sauvegardee ? */
			if ( 98 < event.button.x && event.button.x< 625 && 265 < event.button.y && event.button.y < 355  )
			{
				*choix = lancer_partie_sauvegardee;
				probleme = 0;
			}
			
			/* clic sur quitter ? */
			if ( 539 < event.button.x && event.button.x < 796 && 419< event.button.y && event.button.y < 470 )
			{
				*choix = quitter;
				probleme = 0;
			}	
		}
		else
			if (event.type == SDL_QUIT) /* clic sur la crois en haut de la fenetre*/
				{
				*choix = quitter;
				probleme = 0;
				}
	}
}









