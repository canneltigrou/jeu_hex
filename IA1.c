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
#include "jeu.h"
#include "regle.h"
#include "IA1.h"





void init_tab_IA(CELL tableau[11][11], CASE plateau[11][11])
{
	int i;
	int j;
	for(i=0; i<10; i++)
		for(j=0; j<10; j++)
		{
			tableau[i][j].distance = 0;
			tableau[i][j].couleur = plateau[i][j]; 
		}
}



void propagation_2(CELL tableau[11][11],int compteur, int *trouver,COO cases, PILE *list_cases)
{
	
	
	CELL tmp;	
	COO suite;
	
	/* à gauche */
	tmp = tableau[(cases.x)-1][cases.y]; 
	if(cases.x >0 && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[(cases.x)-1][cases.y].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H || cases.y==10)
		{
			*trouver = 1;
			return ;
		}
		tableau[(cases.x)-1][cases.y].previous = cases;
		suite.x = (cases.x) -1;
		suite.y = cases.y;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
			
	}
	
	
	/* à droite */
	tmp = tableau[(cases.x)+1][cases.y];
	if(cases.x <10 && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[(cases.x)+1][cases.y].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H || cases.y==10)
		{
			*trouver = 1;
			return ;
		}
		
		tableau[(cases.x)+1][cases.y].previous = cases;
		suite.x = (cases.x)+1;
		suite.y = cases.y;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
	}
	
	
	
	/* en bas à gauche */
	tmp = tableau[cases.x][(cases.y)-1];
	if(cases.y > 0 && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[cases.x][(cases.y)-1].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H)
		{
			*trouver = 1;
			return ;
		}
		
		tableau[cases.x][(cases.y)-1].previous = cases;
		suite.x = cases.x;
		suite.y = (cases.y)-1;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
	}
	
	
	/*en bas à droite*/
	tmp = tableau[(cases.x)+1][(cases.y)-1];
	if(cases.y >0 && cases.x <10 && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[(cases.x)+1][(cases.y)-1].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H)
		{
			*trouver = 1;
			return ;
		}
		
		tableau[(cases.x)+1][(cases.y)-1].previous = cases;
		suite.x = (cases.x) +1;
		suite.y = (cases.y)-1;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
	}
	

	/* en haut à droite */
	tmp = tableau[cases.x][(cases.y)+1];
	if(cases.y <10 && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[cases.x][(cases.y)+1].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H || (cases.y) +1==10)
		{
			*trouver = 1;
			return ;
		}
		
		tableau[cases.x][(cases.y)+1].previous = cases;
		suite.x = cases.x;
		suite.y = (cases.y)+1;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
	}
	
	
	
	/* en haut à gauche*/
	tmp = tableau[(cases.x)-1][(cases.y)+1];
	if(cases.x > 0 && cases.y <10  && tmp.distance==0 && (tmp.couleur != bleu && tmp.couleur != bleu_ch_D && tmp.couleur != bleu_ch_G))
	{
		tableau[(cases.x)-1][(cases.y)+1].distance = compteur;
		
		if(tmp.couleur == rouge_ch_H || (cases.y)+1==10)
		{
			*trouver = 1;
			return ;
		}
		
		tableau[(cases.x)-1][(cases.y)+1].previous = cases;
		suite.x = (cases.x) -1;
		suite.y = (cases.y)+1;
		if(tmp.couleur == vide)
			empile(list_cases, suite, personne);

		if(tmp.couleur == rouge || tmp.couleur == rouge_ch_B)
			propagation_2(tableau, compteur, trouver, suite, list_cases);
	}
}


COO depile(PILE* list)
{
	COO retour;
	PILE tmp;
	tmp = (*list)->suivant;
	retour.x = (*list)->x;
	retour.y = (*list)->y;
	free(*list);
	*list = tmp;
	return(retour);
}


void copier(CELL tab_min[11][11], CELL tableau[11][11])
{
	int i;
	int j;
	for (i=0; i<11; i++)
		for (j=0; j<11; j++)
		{
			tab_min[i][j].couleur = tableau[i][j].couleur;
			tab_min[i][j].distance = tableau[i][j].distance;
			tab_min[i][j].previous = tableau[i][j].previous;			
		
		}
	
	
}
	
			
COO recherche_IA1(CASE plateau[11][11])
{
	PILE list_actuelle;
	PILE list_prochaine;
	CELL tableau[11][11];
	/*int minimum;*/
	CELL tab_min[11][11];
	COO gagnant;
	int compteur;
	int nb_iteration_min = 61;
	int x_debut;
	COO cases_a_propager;
	int trouver;
	
	list_actuelle = NULL;
	list_prochaine = NULL;
	
	for(x_debut = 0; x_debut<11; x_debut++)
	{
	init_tab_IA(tableau, plateau);
	compteur = 1;
	trouver = 0;
	cases_a_propager.x = x_debut;
	cases_a_propager.y = 0;
	empile(&list_actuelle, cases_a_propager, personne);
	
	
	
		while (!trouver)
		{
			while(list_actuelle != NULL && !trouver)
			{
				cases_a_propager = depile(&list_actuelle);
				propagation_2(tableau, compteur, &trouver, cases_a_propager, &list_prochaine);
				
				list_actuelle = list_actuelle->suivant;
			}
			if(trouver)
			{
				if(compteur < nb_iteration_min)
				{
					nb_iteration_min = compteur;
					gagnant = cases_a_propager;
					copier(tab_min,tableau);
				}
			}
			else
			{
				list_actuelle = list_prochaine;
				list_prochaine = NULL;
				compteur++;
			}
			
		}
		
	}
	
	/* je récupère désormais le plus court qui ait été trouvé. */
	/* mon chemin le plus court se trouve dann tab_min. */
	
	/* je renvoie le Ier en haut*/
	return(gagnant);
}



	
	
