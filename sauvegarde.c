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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sauvegarde.h"
#include "regle.h"
#include "jeu.h"
#include "display.h"
#define N 16

void charger_une_partie(CASE plateau[11][11], PILE* historique, JOUEUR* Joueur, CHOIX *choix, SDL_Surface ** fenetre, PIONS pion)
{
	FILE *f_in;
	COO coordonnee;
	JOUEUR gagnant;
	char ligne[12];
	ligne[0]='\0';
	gagnant = personne;
	
	f_in = fopen("sauvegarde_de_la_partie.txt", "r");
	if (f_in == NULL)
	{
		printf("aucune partie sauvegardée n'a pu être trouvée. \n");
		*choix = reprendre;
		return ;
	}
	*choix = jouer;
	
	
	/*fseek(f_in, 160*sizeof(char), SEEK_SET);	*/
	fgets(ligne, 15 * sizeof(char), f_in);
	while(strcmp(ligne, "\\game\n") !=0)
		fgets(ligne, 15 * sizeof(char), f_in);

	
	
	fgets(ligne, 15 * sizeof(char), f_in);
	while(strcmp(ligne, "\\endgame\n")!=0)
	{	
		if(ligne[6]=='B')
			*Joueur = jb;
		else
			*Joueur = jr;
		
		coordonnee.x = atoi(&ligne[8]);
		coordonnee.y = atoi(&ligne[10]);
		
		regle(plateau, coordonnee, &gagnant, Joueur, historique);
		ajout_pion (fenetre, pion, coordonnee, *Joueur);
		
		
		fgets(ligne, 15 * sizeof(char), f_in);
	}
	
	fclose(f_in);
}
		

void affiche_tab (CASE plateau[11][11]) /*seulement pour tester. à supp par la  suite*/
{
	int i;
	int j;
	printf("\n\n");
	for (j=10; j>=0; j--)
	{
		for (i=0; i<11; i++)
		{
			if(plateau[i][j]== bleu ||plateau[i][j]== bleu_ch_D || plateau[i][j]== bleu_ch_G)
			{
				printf("B");
				if(plateau[i][j]== bleu_ch_G)
					printf("+");
				if(plateau[i][j]== bleu_ch_D)
					printf("-");
			}
			if(plateau[i][j]==rouge || plateau[i][j]==rouge_ch_H || plateau[i][j]==rouge_ch_B )
			{
				printf("R");
				if(plateau[i][j]== rouge_ch_H)
					printf("+");
				if(plateau[i][j]== rouge_ch_B)
					printf("-");
			}
			if(plateau[i][j]==vide)
				printf(" .");
				
			printf("\t");
		}
		printf("\n");
	}
}



void sauvegarder_une_partie(PILE *historique, CASE plateau[11][11])
{
	FILE *f_out;
	PILE tmp;
	int i;
	int j;
	COO tmpcoo;
	PILE historique2;
	historique2=NULL;
	
	/* je réorganise mon historique dans l'ordre inverse.*/
	tmp = *historique;
	while (tmp != NULL)
	{
		tmpcoo.x = tmp->x;
		tmpcoo.y = tmp->y;
		empile(&historique2, tmpcoo , tmp->joueur);
		tmp = tmp->suivant;
	}
	
	
	tmp = historique2;
	f_out = fopen("sauvegarde_de_la_partie.txt", "w");
	
	fprintf(f_out, "\\hex.\n\\board\n");

	for (j=10; j>=0; j--)
	{
		for (i=0; i<11; i++)
		{
			if(plateau[i][j]== bleu ||plateau[i][j]== bleu_ch_D || plateau[i][j]== bleu_ch_G)
				fprintf(f_out, "B");
			if(plateau[i][j]==rouge || plateau[i][j]==rouge_ch_H || plateau[i][j]==rouge_ch_B )
				fprintf(f_out, "R");
			if(plateau[i][j]==vide)
				fprintf(f_out, ".");
		}
		fprintf(f_out,"\n");
	}
	fprintf(f_out, "\\endboard\n");
	fprintf(f_out, "\\game\n");
	
	while (tmp != NULL)
	{
		
		fprintf(f_out, "\\play ");
		if (tmp->joueur == jb)
			fprintf(f_out, "B ");
		else
			fprintf(f_out, "R ");
				
		fprintf(f_out, "%d %d\n", tmp->x , tmp->y);
		tmp = tmp->suivant;
	}

	fprintf(f_out, "\\endgame\n\\endhex");
	fclose(f_out);
}



/*RAPPEL : 
void propagation(CASE *plateau[], COO cases, CASE couleur, CASE a_remplacer) */

void option_reculer(PILE* historique, CASE plateau[11][11], JOUEUR *joueur, COO *coordonnees)
{
	CASE couleur;
	COO cases;
	COO case2;
	int i;
	
	if(*historique == NULL)
		return ;
	
	cases.x = (*historique)->x;
	cases.y = (*historique)->y;
	couleur = plateau[(*historique)->x][(*historique)->y];
	coordonnees->x = cases.x;
	coordonnees->y = cases.y;
	*joueur = (*historique)->joueur;
	
	/*je dépile mon historique en rendant la dernière case jouée 'vide' */
	plateau[(*historique)->x][(*historique)->y] = vide;
	
	*historique = (*historique)->suivant;
	
	/* je redépropage si couleur spéciale avant de reregarder les bord pour repropager.*/
	if (couleur == rouge_ch_H || couleur == rouge_ch_B)
	{
		propagation(plateau, cases, couleur, rouge);
		if (couleur == rouge_ch_H)
		{
			for(i=0; i<11; i++)
			{
				if (plateau[i][10] == rouge)
				{
					plateau[i][10] = rouge_ch_H;
					case2.x = i;
					case2.y = 10;
					propagation(plateau, case2, rouge_ch_H, rouge);
				}
			}
		}
		else
		{
			for(i=0; i<11; i++)
			{
				if (plateau[i][0] == rouge)
				{
					plateau[i][0] = rouge_ch_B;
					case2.x = i;
					case2.y = 0;
					propagation(plateau, case2, rouge_ch_B, rouge);
				}
			}
		}
	}

	if (couleur==bleu_ch_G || couleur==bleu_ch_D)
	{
		propagation(plateau, cases, couleur, bleu);
		if (couleur == bleu_ch_G)
		{
			for(i=0; i<11; i++)
			{
				if (plateau[0][i] == bleu)
				{
					plateau[0][i] = bleu_ch_G;
					case2.x = 0;
					case2.y = i;
					propagation(plateau, case2, bleu_ch_G, bleu);
				}
			}
		}
		else
		{
			for(i=0; i<11; i++)
			{
				if (plateau[10][i] == bleu)
				{
					plateau[10][i] = bleu_ch_D;
					case2.x = 10;
					case2.y = i;
					propagation(plateau, case2, bleu_ch_D, bleu);
				}
			}
		}
	}
}
