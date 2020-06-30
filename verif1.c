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



#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "regle.h"
#include "sauvegarde.h"
#include "display.h"
#include "verif1.h"



COO depile_verif(pile_verif* ma_pile, CHOIX* option)
{
	COO retour;
	pile_verif tmp;
	tmp = (*ma_pile)->suivant;
	retour = (*ma_pile)->cases;
	*option = (*ma_pile)->option;
	free(*ma_pile);
	*ma_pile = tmp;
	return(retour);
}

void empile_verif(pile_verif* ma_pile,CHOIX option, int x, int y)
{

	pile_verif new_cell;
	new_cell = (pile_verif)malloc(sizeof(struct Pile_verif));
	(new_cell->cases).x = x;
	(new_cell->cases).y = y;
	new_cell->option = option;
	new_cell->suivant = *ma_pile;
	*ma_pile = new_cell;
		
}


int fonction_principale(pile_verif *ma_pile, int fonction)
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
	int compteur;

	
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
	compteur = 0;
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
	
		joueur = jr; /* en considérant que rouge commence toujours pour l'instant */
		
		
		/* création graphique du menu et envoie de la réponse*/
		maj_fenetre (&fenetre, menu_window, gris);
		//detection_clic_menu(&choix);
		depile_verif(ma_pile, &choix);
		compteur++;
		sleep(1);
		
/**************** dans tous les cas, on arrive maintenant au jeu*************/
	
		
		if (choix != quitter)
		{
			/* lancement du plateau graphique sdl */	
			maj_fenetre (&fenetre, board_window, gris);
			print_tour (&fenetre, tourjoueur, joueur);
		}
		
		if (choix == lancer_partie_sauvegardee)
		{
			printf("\n\nje lance une partie déjà sauvegardée\n");			
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
			//detection_clic_jeu(&choix, &cases);
			cases = depile_verif(ma_pile, &choix);
			compteur++;
			sleep(1);
			
			
			if(choix == sauvegarder)
			{
				sauvegarder_une_partie(&historique, plateau);
				printf("\n\nJe sauvegarde ma partie.\n");
			}
			
			if (choix == undo)
			{
				printf("\n\nJe fais un retour en arrière n°%d\n", compteur);
				option_reculer(&historique, plateau, &joueur, &cases);
				/* remettons à jour l'affichage sdl*/
				ajout_pion(&fenetre, pions, cases, personne);
				print_tour(&fenetre, tourjoueur, joueur);
				print_historique1 (&fenetre, historique, couleurNoire, police);
			}
			
			if(choix == historique_aff)
			{
				printf("\n\n j'affiche l'historique\n");
				print_historique2 (historique, &fenetre, hist_window, couleurNoire, police, gris );
			}
			
			if (choix == jouer)
			{
				probleme = regle(plateau, cases, &gagnant, &joueur, &historique ); /*regarde si le coup est jouable. si oui, cette fct modifie le plateau et le joueur. puis elle regarde s'il y a un gagnant. si c'est le cas, elle modifie la variable gagnant.*/
			
				if(!probleme || gagnant != personne)
				{
					ajout_pion(&fenetre, pions, cases, joueur);
					print_tour (&fenetre, tourjoueur, joueur);
					print_historique1 (&fenetre, historique, couleurNoire, police);
				
				}
				
				
				
				/*affiche_tab (plateau);*/
			}
			if (compteur == 11 && fonction==1)
			{
				/* test1*/
				printf("\033[22;34m\nun Rouge en relation avec un coté rouge touche un bleu en relation avec un coté bleu. Verifions que'il e détecte pas de gagnant\n\033[0m");
				if (gagnant == personne)
					printf("\033[22;34m\nModule règle, fct gagnant : test 1 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nModule règle, fct gagnant : test 1 KO\n\n\033[0m");
			}
			if (fonction==1 && compteur == 22)
			{
				printf("\033[22;34m\nle rouge vient de jouer %d , %d ce qui le fait normalement gagner. vérifions que c'est le cas.\n\033[0m", cases.x, cases.y);
				if (gagnant == jr)
					printf("\033[22;34m\nModule règle, fct gagnant : test 2 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nModule règle, fct gagnant : test 2 KO\n\n\033[0m");
			}
			if (fonction==2 && compteur == 30)
			{ 	printf("\033[22;34m\nrouge a normalement gagné. vérifions.\n\n\033[0m");
				if (gagnant == jr)
					printf("\033[22;34m\nModule règle, fct gagnant : test 3 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nModule règle, fct gagnant : test 3 KO\n\n\033[0m");
			}
			
			
			if (fonction == 4 && compteur == 4)
			{
				printf("\033[22;34m\nvérifions l'historique\nJe dois avoir pour dernier coup x=2 et y=9\n\033[0m");
				if (historique->x == 2 && historique->y == 9)
					printf("\033[22;34m\nfonction historique : test 1 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nfonction historique : test 1 KO\n\n\033[0m");
			}
			if (fonction ==4 && compteur == 12)
			{
				printf("\033[22;34m\n je viens de demander un undo. Vérifions que la derniere case jouée (la 1; 6 est bien vide désormais.\n\033[0m");
				if (plateau[1][6]==vide)
					printf("\033[22;34m\nfonction undo : test 1 OK\n\033[0m");
				else
					printf("\033[22;34m\nfonction undo : test 1 KO\n\033[0m");
				
				printf("\033[22;34m\nvérifions également l'historique après cet undo\nJe dois ici avoir x = 2 et y = 6\n\033[0m");
				if (historique->x == 2 && historique->y == 6)
					printf("\033[22;34m\nfonction undo : test 2 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nfonction undo : test 2 KO\n\n\033[0m");
			}
			if (fonction == 4 && compteur == 29)
			{
				printf("\033[22;34m\nj'ai fait 3 fois undo avec mon plateau déjà vide avant de rejouer normalement. Vérifions que la case que nous venons de jouer (Rouge 2; 10) est correcte\n\n\033[0m");
				if (plateau[2][10]==rouge_ch_H)
					printf("\033[22;34m\nfonction undo : test 3 OK\n\n\033[0m");
				else
					printf("\033[22;34m\nfonction undo : test 3 KO\n\n\033[0m");
					
			
			}
			
			
			
			
			
			
		
		} /* soit un gagnant est trouvé, soit l'utilisateur veut  quitter*/
		
		
		if (gagnant != personne)
		{	sleep(1);
			/* sdl pour afficher le gagnant*/
			print_gagnant(&fenetre, gagnant, &choix);
		}
		vider_historique(&historique);
	}
	
		/* libération des surfaces SDL en mémoire et fermeture de la fenetre et de TTF*/
		printf("\n\nje quitte le jeu\n");
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






void fonction1(void)
{
	pile_verif ma_pile;
	empile_verif(&ma_pile, quitter, 0, 0);
	empile_verif(&ma_pile, quitter, 0, 0);
	empile_verif(&ma_pile, jouer, 2, 0);
	empile_verif(&ma_pile, jouer, 4, 1);
	empile_verif(&ma_pile, jouer, 2, 1);
	empile_verif(&ma_pile, jouer, 6, 1);
	empile_verif(&ma_pile, jouer, 2, 2);
	empile_verif(&ma_pile, jouer, 5,3);
	empile_verif(&ma_pile, jouer,2, 3);
	empile_verif(&ma_pile, jouer,5, 4);
	empile_verif(&ma_pile, jouer, 2,4);
	empile_verif(&ma_pile, jouer,3, 5);
	empile_verif(&ma_pile, jouer,2, 5);
	empile_verif(&ma_pile, jouer, 1, 6);
	empile_verif(&ma_pile, jouer,2, 6);
	empile_verif(&ma_pile, jouer,0, 6);
	empile_verif(&ma_pile, jouer,2, 7);
	empile_verif(&ma_pile, jouer,5, 6);
	empile_verif(&ma_pile, jouer,2, 8);
	empile_verif(&ma_pile, jouer,4, 8);
	empile_verif(&ma_pile, jouer,2, 9);
	empile_verif(&ma_pile, jouer, 1, 9);
	empile_verif(&ma_pile, jouer, 2, 10);
	empile_verif(&ma_pile, jouer, 0, 0);
	
	fonction_principale(&ma_pile, 1);

}

void fonction2(void)
{
	pile_verif ma_pile;
	empile_verif(&ma_pile, quitter, 0, 0);
	empile_verif(&ma_pile, quitter, 0, 0);
	empile_verif(&ma_pile, jouer, 4, 2);
	empile_verif(&ma_pile, jouer, 1,3);
	empile_verif(&ma_pile, jouer,4, 1);
	empile_verif(&ma_pile, jouer, 3, 0);
	empile_verif(&ma_pile, jouer, 4, 0);
	empile_verif(&ma_pile, jouer, 7, 2);
	empile_verif(&ma_pile, jouer, 4, 5);
	empile_verif(&ma_pile, jouer, 6,3);
	empile_verif(&ma_pile, jouer, 5,4);
	empile_verif(&ma_pile, jouer, 3, 2);
	empile_verif(&ma_pile, jouer, 5, 3);
	empile_verif(&ma_pile, jouer, 4, 4);
	empile_verif(&ma_pile, jouer, 5, 2);
	empile_verif(&ma_pile, jouer, 3, 3);
	empile_verif(&ma_pile, jouer, 3, 4);
	empile_verif(&ma_pile, jouer, 6, 6);
	empile_verif(&ma_pile, jouer, 2, 8);
	empile_verif(&ma_pile, jouer, 5, 9);
	empile_verif(&ma_pile, jouer, 1, 9);
	empile_verif(&ma_pile, jouer, 5, 8);
	empile_verif(&ma_pile, jouer, 0, 10);
	empile_verif(&ma_pile, jouer,5, 7);
	empile_verif(&ma_pile, jouer, 3,7);
	empile_verif(&ma_pile, jouer, 5, 7);
	empile_verif(&ma_pile, jouer,3, 7);
	empile_verif(&ma_pile, jouer, 5, 6);
	empile_verif(&ma_pile, jouer, 3, 6);
	empile_verif(&ma_pile, jouer, 6, 5);
	empile_verif(&ma_pile, jouer, 3, 5);
	empile_verif(&ma_pile, jouer,3, 5);
	
	fonction_principale(&ma_pile, 2);

}

void fonction4(void)
{
	pile_verif ma_pile;
	empile_verif(&ma_pile, quitter,0, 0);
	empile_verif(&ma_pile, jouer, 4, 4);
	empile_verif(&ma_pile, undo, 0, 0);
	empile_verif(&ma_pile, jouer, 1, 6);
	empile_verif(&ma_pile, jouer, 2, 6);
	empile_verif(&ma_pile, jouer, 0, 6);
	empile_verif(&ma_pile, jouer, 2, 10);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, undo,0, 0);
	empile_verif(&ma_pile, jouer, 1, 6);
	empile_verif(&ma_pile, jouer, 4, 4);
	empile_verif(&ma_pile, undo, 0, 0);
	empile_verif(&ma_pile, jouer, 1, 6);
	empile_verif(&ma_pile, jouer, 2, 6);
	empile_verif(&ma_pile, jouer, 0, 6);
	empile_verif(&ma_pile, jouer, 2, 7);
	empile_verif(&ma_pile, jouer, 5, 6);
	empile_verif(&ma_pile, jouer, 2, 8);
	empile_verif(&ma_pile, jouer, 4, 8);
	empile_verif(&ma_pile, jouer,2, 9);
	empile_verif(&ma_pile, jouer, 1, 9);
	empile_verif(&ma_pile, jouer, 2, 10);
	empile_verif(&ma_pile, jouer, 2, 10);
	
	fonction_principale(&ma_pile, 4);
	
}

void fonction5(void)
{
	pile_verif ma_pile;

	empile_verif(&ma_pile, quitter, 4, 4);
	empile_verif(&ma_pile, quitter, 0, 0);
	empile_verif(&ma_pile, jouer, 2, 6);
	empile_verif(&ma_pile, jouer, 0, 6);
	empile_verif(&ma_pile, lancer_partie_sauvegardee, 0, 6);
	empile_verif(&ma_pile, reprendre, 2, 6);
	empile_verif(&ma_pile, jouer, 2, 6);
	empile_verif(&ma_pile, jouer, 0, 6);
	empile_verif(&ma_pile, sauvegarder, 4, 3);
	empile_verif(&ma_pile, jouer,4,3);
	empile_verif(&ma_pile, jouer, 3,4);
	empile_verif(&ma_pile, jouer, 2, 3);
	empile_verif(&ma_pile, jouer, 2, 3);
	
	fonction_principale(&ma_pile, 5);
	
	empile_verif(&ma_pile, quitter, 2,6);
	empile_verif(&ma_pile, quitter, 2,6);
	empile_verif(&ma_pile, jouer, 2,6);
	empile_verif(&ma_pile, jouer, 0, 6);
	empile_verif(&ma_pile, lancer_partie_sauvegardee, 2, 3);
	
	fonction_principale(&ma_pile, 6);
	
	
	
}





int main(void)
{
	
	fonction1();
	
	fonction2();
	
	fonction4();
	
	fonction5();

	return(0);
}


