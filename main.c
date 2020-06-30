#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"
#include "regle.h"
#include "sauvegarde.h"
#include "display.h"
#include "IA1.h"



int main(void)
{
	/*initialisation du plateau*/
	CASE plateau[11][11];
	int i;
	int j;
	int probleme; /* prend pour valeur 1 lors d'un problème ou parfois lors d'un gagnant*/
	CHOIX choix;
	COO cases;
	JOUEUR gagnant;
	JOUEUR joueur;
	PILE historique;
	bool IA; /* pour m'en souvenir malgre le changement des options*/
//	COO IA_extremite1;
//	COO IA_extremite2;
//	IA_extremite1.x = -1;

	
	
	/*----------------------------------------------------------------------*/
	/*----------------------- Creation fenetre SDL -------------------------*/
	SDL_Surface *fenetre=NULL;
	SDL_Surface *menu_window = NULL;
	SDL_Surface *board_window = NULL;
	SDL_Surface *hist_window=NULL;
	TTF_Font *police = NULL;
	PIONS pions;
	Uint32  gris;
	sdlTOUR tourjoueur;
	SDL_Color couleurNoire = {0,0,0,0};
	

	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "erreur dans l'initialisation de SDL");
		exit(EXIT_FAILURE);
	}
	
	if(TTF_Init()==-1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init");
		exit(EXIT_FAILURE);	
	}
	
	police = TTF_OpenFont("Velocette.ttf", 30);
	
	putenv("SDL_VIDEO_WINDOW_POS=center");
	
	/* je lance une nouvelle fenetre*/
	fenetre = SDL_SetVideoMode(	WIDTH, HEIGHT, 32, SDL_HWSURFACE);
	if (fenetre == NULL)
		exit(EXIT_FAILURE);
	
	/* Mise en place d'un titre à la fenêtre */
	SDL_WM_SetCaption("Hex", NULL); 
	
	init_fenetres(&menu_window, &board_window, &pions , &tourjoueur, &hist_window);
	
	/*je rentre en mémoire ma couleur */	
	gris = SDL_MapRGB(fenetre->format, 192, 192, 192);
	
	

	/* --------------------------------------------------------------*/
	/*-----------------------------------------------------------------*/
	
	choix = reprendre;
	while (choix == reprendre)
	{
		
		
		/* initialisation de mon plateau matrice */
		for (i=0; i<11; i++)
			for (j=0; j<11; j++)
				plateau[i][j] = vide;
		
		historique = NULL;
		gagnant = personne;
		probleme = 0;
		IA = 0;
		joueur = jr; /* en considérant que rouge commence toujours pour l'instant */
		
		
		/* création graphique du menu et envoie de la réponse*/
		maj_fenetre (&fenetre, menu_window, gris);
		detection_clic_menu(&choix);
		
/**************** dans tous les cas, on arrive maintenant au jeu*************/
		
		if (choix== IA1)
			IA = 1;
		
		if (choix != quitter)
		{
			/* lancement du plateau graphique sdl */	
			maj_fenetre (&fenetre, board_window, gris);
			print_tour (&fenetre, tourjoueur, joueur);
		}
		
		if (choix == lancer_partie_sauvegardee)
		{
			charger_une_partie(plateau, &historique, &joueur, &choix, &fenetre, pions); /* fonction permettant de remplir le plateau comme il se doit avec ma partie sauvegardée.*/
			print_historique1 (&fenetre, historique, couleurNoire, police);
			print_tour(&fenetre, tourjoueur, joueur);
		}

		/* le jeu peut commencer*/
		while (gagnant == personne && choix!= quitter && choix != reprendre)
		{
			probleme = 0;
			if (choix==undo || choix==sauvegarder || choix == historique_aff)	
				choix = jouer;
			
			/* demande de part sdl quelle case ou option est choisie */
			detection_clic_jeu(&choix, &cases);
			
			
			
			if(choix == sauvegarder)
				sauvegarder_une_partie(&historique, plateau);
			
			if (choix == undo)
			{
				option_reculer(&historique, plateau, &joueur, &cases);
				/* remettons à jour l'affichage sdl*/
				ajout_pion(&fenetre, pions, cases, personne);
				print_tour(&fenetre, tourjoueur, joueur);
				print_historique1 (&fenetre, historique, couleurNoire, police);
			}
			
			if(choix == historique_aff)
				print_historique2 (historique, &fenetre, hist_window, couleurNoire, police, gris );
			
			if (choix == jouer)
			{
				probleme = regle(plateau, cases, &gagnant, &joueur, &historique ); /*regarde si le coup est jouable. si oui, cette fct modifie le plateau et le joueur. puis elle regarde s'il y a un gagnant. si c'est le cas, elle modifie la variable gagnant.*/
			
				if(!probleme)
				{
					ajout_pion(&fenetre, pions, cases, joueur);
					print_tour (&fenetre, tourjoueur, joueur);
					print_historique1 (&fenetre, historique, couleurNoire, police);
				
				}
				affiche_tab (plateau);
			}
				
			if (IA && !probleme)
			{
				/* SEULEMENT affichage de SDL */
				sleep(1); /* permet un leger temps d'attente pour voir ce que joue l'IA*/
				cases = recherche_IA1(plateau);
				regle(plateau, cases, &gagnant, &joueur, &historique);
				ajout_pion(&fenetre, pions, cases, joueur);
				affiche_tab (plateau);
			}
		
		} /* soit un gagnant est trouvé, soit l'utilisateur veut  quitter*/
		
		
		if (gagnant != personne)
		{	/* sdl pour afficher le gagnant*/
			printf("gagné :P");
			print_gagnant(&fenetre, gagnant, &choix);
		}
		vider_historique(&historique);
	}
	
		/* libération des surfaces SDL en mémoire et fermeture de la fenetre et de TTF*/
		SDL_FreeSurface(fenetre);
		SDL_FreeSurface(menu_window);
		SDL_FreeSurface(board_window);
		SDL_FreeSurface(pions.pion_rouge);
		SDL_FreeSurface(pions.pion_bleu);
		SDL_FreeSurface(pions.pion_vide);
		SDL_FreeSurface(tourjoueur.tour_rouge);
		SDL_FreeSurface(tourjoueur.tour_bleu);
		SDL_FreeSurface(hist_window);
		TTF_CloseFont(police);
		TTF_Quit();
		SDL_Quit();
	
	return 0;
}
