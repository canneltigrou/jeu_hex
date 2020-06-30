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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"
#include "detection_case.h"


void init_fenetres (SDL_Surface **menu_window, SDL_Surface **board_window, PIONS * pions, sdlTOUR * tourjoueur, SDL_Surface **hist_window )
{
	
	/* je rentre en mémoire ma surface menu */	
	*menu_window = IMG_Load("image/menu.png");
	if(!*menu_window)
	{	
		fprintf(stderr, "erreur : image menu non valide");
		exit(EXIT_FAILURE);
	}
	
	
	/* je rentre en mémoire ma surface plateau */	
	*board_window = IMG_Load("image/jeu_hex_board.png");
	if(!*board_window)
	{	
		fprintf(stderr, "erreur : image plateau non valide");
		exit(EXIT_FAILURE);
	}
	
	/* je rentre en memoire la surface fond de l'affichage de l'historique*/
	*hist_window = IMG_Load("image/historique_aff.png");
	if(!*hist_window)
	{	
		fprintf(stderr, "erreur : image de l'historique non valide");
		exit(EXIT_FAILURE);
	}
	
	/* je rentre en memoire les pions.*/
	pions->pion_rouge = IMG_Load("image/button-red22.png");
	pions->pion_bleu = IMG_Load("image/button-blue22.png");
	pions->pion_vide = IMG_Load("image/button-vide22.png");
	
	if(!(pions->pion_rouge) || !(pions->pion_bleu) || !(pions->pion_vide))
	{	
		fprintf(stderr, "erreur : image pion non valide");
		exit(EXIT_FAILURE);
	}
	
	/* je rentre en memoire les joueurs */
	tourjoueur->tour_rouge = IMG_Load("image/tour_jr.png");
	tourjoueur->tour_bleu = IMG_Load("image/tour_jb.png");
	if(!(tourjoueur->tour_bleu) || !(tourjoueur->tour_rouge))
	{	
		fprintf(stderr, "erreur : image tour_joueur non valide");
		exit(EXIT_FAILURE);
	}
	
}


void maj_fenetre (SDL_Surface ** fenetre, SDL_Surface *a_mettre, Uint32 couleur)
{
	/* je réinitialise ma fenetre */
	SDL_FillRect(*fenetre, NULL, couleur);
	SDL_Flip(*fenetre);
	
	/* je replace mon plateau */
	SDL_Rect a_mettre_position;
	a_mettre_position.x = 0;
	a_mettre_position.y =0;
	SDL_BlitSurface(a_mettre, NULL, *fenetre, &a_mettre_position);
	SDL_Flip(*fenetre);

}






void print_tour (SDL_Surface ** fenetre, sdlTOUR tourjoueur, JOUEUR joueur)
{
	SDL_Rect tourPosition;
	tourPosition.x = 65;
	tourPosition.y = 25;
	
	if(joueur == jb)
		SDL_BlitSurface(tourjoueur.tour_bleu, NULL, *fenetre, &tourPosition);
	else
		SDL_BlitSurface(tourjoueur.tour_rouge, NULL, *fenetre, &tourPosition);
			
	SDL_Flip(*fenetre);

}

void print_historique1 (SDL_Surface ** fenetre, PILE historique, SDL_Color couleurNoire, TTF_Font *police)
{
	
	Uint32 gris;
	SDL_Surface *texte;
	SDL_Rect position;
	
	/* je replace un rectangle gris pour affacer le précédent*/
	SDL_Surface *cache;
	SDL_Rect cache_position;
	gris = SDL_MapRGB((*fenetre)->format, 192, 192, 192);
	cache = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 50, 32, 0,0,0,0);
	SDL_FillRect(cache, NULL, gris);
	cache_position.x = 504;
	cache_position.y = 440;
	SDL_BlitSurface(cache, NULL, *fenetre, &cache_position);
	SDL_Flip(*fenetre);
	
	if (historique == NULL)
		return ;
	
	position.y = 440;
	char hist[3];
	sprintf(hist, "%d", historique->x);
	texte = TTF_RenderText_Blended(police, hist, couleurNoire);
	position.x = 505;
	SDL_BlitSurface(texte, NULL, *fenetre, &position);
	SDL_Flip(*fenetre);
	SDL_FreeSurface(texte);
	
	sprintf(hist, "%d", historique->y);
	texte = TTF_RenderText_Blended(police, hist, couleurNoire);
	position.x = 550;
	SDL_BlitSurface(texte, NULL, *fenetre, &position);
	SDL_Flip(*fenetre);
	SDL_FreeSurface(texte);
	
}


void print_historique2 (PILE historique, SDL_Surface** fenetre, SDL_Surface *hist_window, SDL_Color couleurNoire, TTF_Font *police, Uint32 couleur )
{
	int fermeture;
	int compteur;
	PILE tmp;
	SDL_Event event;
	SDL_Surface *texte;
	SDL_Rect text_position;
	SDL_Rect fenetre_position;
	char hist[3];
	char* j_gauche = malloc(8 * sizeof(char));
	char* j_droite = malloc(8 * sizeof(char));
	SDL_Surface *retour_plateau=NULL;
	
	if (historique->joueur == jb)
	{
		j_gauche = strcpy(j_gauche, "j.bleu");
		j_droite = strcpy(j_droite, "j.rouge");
	}
	else
	{
		j_gauche = strcpy(j_gauche, "j.rouge");
		j_droite = strcpy(j_droite, "j.bleu");
	}
	
	/* je sauvegarde l'etat actuel de ma fenetre plateau dans un fichier image*/
	SDL_SaveBMP(*fenetre, "image/retour_plateau.bmp");

	SDL_FillRect(*fenetre, NULL, couleur); /* remise d'une fenetre vierge*/
	SDL_Flip(hist_window);
	
	fenetre_position.x = 0;
	fenetre_position.y =0;
	SDL_BlitSurface(hist_window, NULL, *fenetre, &fenetre_position);
	SDL_Flip(*fenetre);
	

	
	/* je n'affiche que les 32 derniers coups dans l'ordre du plus récent au plus ancien */
	compteur = 0;
	tmp = historique;
	while(compteur <16 && tmp != NULL) /* ie 16 lignes de 2 coordonnées */
	{
		
		text_position.y = 120 + 20*compteur;
		
		/* affichage du joueur*/
		text_position.x = 100;
		texte = TTF_RenderText_Blended(police, j_gauche, couleurNoire);
		SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
		SDL_Flip(*fenetre);
		SDL_FreeSurface(texte);
		
		/* affichage du x*/
		sprintf(hist, "%d", tmp->x);
		texte = TTF_RenderText_Blended(police, hist, couleurNoire);
		text_position.x = 205;
		SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
		SDL_Flip(*fenetre);
		SDL_FreeSurface(texte);
		
		/* affichage du y*/
		sprintf(hist, "%d", tmp->y);
		texte = TTF_RenderText_Blended(police, hist, couleurNoire);
		text_position.x = 250;
		SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
		SDL_Flip(*fenetre);
		SDL_FreeSurface(texte);
		
		tmp = tmp->suivant;
		if(tmp != NULL)
		{
			text_position.x = 400;
			texte = TTF_RenderText_Blended(police, j_droite, couleurNoire);
			SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
			SDL_Flip(*fenetre);
			SDL_FreeSurface(texte);
			
			sprintf(hist, "%d", tmp->x);
			texte = TTF_RenderText_Blended(police, hist, couleurNoire);
			text_position.x = 505;
			SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
			SDL_Flip(*fenetre);
			SDL_FreeSurface(texte);
		
			sprintf(hist, "%d", tmp->y);
			texte = TTF_RenderText_Blended(police, hist, couleurNoire);
			text_position.x = 550;
			SDL_BlitSurface(texte, NULL, *fenetre, &text_position);
			SDL_Flip(*fenetre);
			SDL_FreeSurface(texte);
			
			tmp = tmp->suivant;
		}
		compteur++;
	}
	

	fermeture = 0;
	while (!fermeture)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			fermeture = 1;
	}
	/* l'utilisateur vient de fermer la fenetre:
	je remets le plateau du jeu.*/
	retour_plateau = IMG_Load("image/retour_plateau.bmp");
	
	SDL_FillRect(*fenetre, NULL, couleur);
	SDL_Flip(hist_window);
	SDL_BlitSurface(retour_plateau, NULL, *fenetre, &fenetre_position);
	SDL_Flip(*fenetre);
	free(retour_plateau);
}



void ajout_pion (SDL_Surface ** fenetre, PIONS pion, COO cases, JOUEUR joueur)
{
	
	COO rectangle_BG; /* défini plus haut */
	COO hexagone_H;
	SDL_Rect pionPosition;
	SDL_Surface *pion_a_placer;
	if(joueur==jb)
		pion_a_placer = pion.pion_rouge;
	if(joueur == jr)
		pion_a_placer = pion.pion_bleu;
	if(joueur == personne) /* appelé dans le cas d'un undo*/
		pion_a_placer = pion.pion_vide;
	
	rectangle_BG.x = 399;
	rectangle_BG.y = 83;
	hexagone_H.x = 417;
	hexagone_H.y = 52;
		

	/* remarque : les coordonnées de la toute première boule en haut à gauche serait (406, 62)*/
	pionPosition.y = 62+(10 - cases.y)*(rectangle_BG.y - hexagone_H.y);
	pionPosition.x = 406 + (hexagone_H.x - rectangle_BG.x)*(2*cases.x - (10 - cases.y));
	SDL_BlitSurface(pion_a_placer, NULL, *fenetre, &pionPosition);
	SDL_Flip(*fenetre);
	//SDL_BlitSurface(pion_a_placer, NULL, *,  &pionPosition);
}


void print_gagnant(SDL_Surface **fenetre, JOUEUR gagnant, CHOIX * choix)
{
	SDL_Event event;
	int je_quitte;
	SDL_Surface *victoire;
	SDL_Rect victoirePosition;
	if(gagnant == jb)
		victoire = IMG_Load("image/gagnant_bleu.png");
	else
		victoire = IMG_Load("image/gagnant_rouge.png");
		
	if(!victoire)
	{	
		fprintf(stderr, "erreur : image non valide");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(victoire, NULL, *fenetre, &victoirePosition);
	SDL_Flip(*fenetre);
	
	je_quitte = 0;
	while(!je_quitte)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			je_quitte = 1;
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				*choix = reprendre;
				je_quitte = 1;
			}	
	}
}


