/***********************************************************************************
 *__________                   __        __         ___ __________________  ___    *     
 *\______   \_______  ____    |__| _____/  |_      /   |   \_   _____/\   \/  /    *           
 * |     ___/\_  __ \/  _ \   |  |/ __ \   __\    /    ~    \    __)_  \     /     *  
 * |    |     |  | \(  <_> )  |  \  ___/|  |      \    Y    /        \ /     \ 	   *
 *|____|     |__|   \____/\__|  |\___  >__|       \___|_  /_______  //___/\  \	   *
 *                      \______|                                                   *           
 *											    								   *
 *			regle  par Mevolhon Claire et Monge Brian      	                       *
 *                                                             	                   *
 **********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "regle.h"
#include "jeu.h"



/* {vide, bleu, rouge, bleu_ch_G, bleu_ch_D, rouge_ch_H, rouge_ch_B }CASE; */


/* les cases adjacentes à (i, j):
 - (i-1 ; j) à gauche
 - (i+1 ; j) à droite
 - (i ; j-1) en bas à gauche
 - (i+1 ; j-1)en bas à droite
 - (i; j+1) en haut à droite
 - (i-1 ; j+1) en haut à gauche
(en considérant pour centre du repère : en bas à gauche)*/ 
/* il faut donc 0<=i<=10 et 0<=j<=10 */
 
 /* je définis les rouge de bas à haut et les bleu de gauche à droite */


void propagation(CASE plateau[11][11], COO cases, CASE couleur, CASE a_remplacer)
{
	/*CASE a_remplacer;*/
	COO suite;
	/*if (couleur == rouge_ch_H || couleur == rouge_ch_B)
		a_remplacer = rouge;
	else
		a_remplacer = bleu;
	*/
	if (cases.x >0 && plateau[(cases.x) -1][cases.y] == a_remplacer)
	{
		plateau[(cases.x)-1][cases.y] = couleur;
		suite.x = (cases.x) -1;
		suite.y = cases.y;
		propagation(plateau, suite, couleur, a_remplacer);
	}
	
	if (cases.x <10 && plateau[(cases.x) +1][cases.y] == a_remplacer)
	{
		plateau[(cases.x)+1][cases.y] = couleur;
		suite.x = (cases.x) +1;
		suite.y = cases.y;
		propagation(plateau, suite, couleur, a_remplacer);
	}
	
	if (cases.y >0 && plateau[cases.x][(cases.y) -1] == a_remplacer)
	{
		plateau[cases.x][(cases.y) -1] = couleur;
		suite.x = cases.x;
		suite.y = (cases.y) -1;
		propagation(plateau, suite, couleur, a_remplacer);
	}

	if (cases.y >0 && cases.x <10 && plateau[(cases.x)+1][(cases.y) -1] == a_remplacer)
	{
		plateau[(cases.x)+1][(cases.y) -1] = couleur;
		suite.x = (cases.x)+1;
		suite.y = (cases.y) -1;
		propagation(plateau, suite, couleur, a_remplacer);
	}

	if (cases.y <10 && plateau[cases.x][(cases.y) +1] == a_remplacer)
	{
		plateau[cases.x][(cases.y) +1] = couleur;
		suite.x = cases.x;
		suite.y = (cases.y) +1;
		propagation(plateau, suite, couleur, a_remplacer);
	}
	
	if (cases.x > 0 && cases.y < 10 && plateau[(cases.x)-1][(cases.y) +1] == a_remplacer)
	{
		plateau[(cases.x)-1][(cases.y) +1] = couleur;
		suite.x = (cases.x)-1;
		suite.y = (cases.y) +1;
		propagation(plateau, suite, couleur, a_remplacer);
	}
}

void empile (PILE* historique, COO coordonnees, JOUEUR joueur)
{

	PILE new_cell;
	new_cell = (PILE)malloc(sizeof(struct pile));
	new_cell->x = coordonnees.x;
	new_cell->y = coordonnees.y;
	new_cell->joueur = joueur;
	new_cell->suivant = *historique;
	*historique = new_cell;
		
}



int regle(CASE plateau[11][11], COO cases, JOUEUR * gagnant, JOUEUR * joueur, PILE *historique)
{
	if (plateau[cases.x][cases.y]!= vide)
	{
		fprintf(stdout, "cette case %d;%d est déjà occupée", cases.x, cases.y);
		return(1);
	}
	
	
	if (*joueur == jr)
	{
		plateau[cases.x][cases.y] = rouge;
		/* j'empile mon historique*/
		empile(historique, cases, *joueur);		
		
		if (cases.y==10)
		{
			plateau[cases.x][cases.y] = rouge_ch_H;
			if (plateau[cases.x][9]==rouge_ch_B)
			{
				*gagnant = jr;
				return(1);
			}
			if (cases.x<10 && plateau[(cases.x)+1][9] == rouge_ch_B)
			{
				*gagnant = jr;
				return(1);
			}
			
			propagation(plateau, cases, rouge_ch_H, rouge);
						
		}
		
		if (cases.y==0)
		{
			plateau[cases.x][cases.y] = rouge_ch_B;
			if (plateau[cases.x][1]==rouge_ch_H)
			{
				*gagnant = jr;
				return(1);
			}
			if (cases.x > 0 && plateau[(cases.x)-1][1] == rouge_ch_H)
			{
				*gagnant = jr;
				return(1);
			}
			
			propagation(plateau, cases, rouge_ch_B, rouge);			
		}
		
		if (cases.y > 0 && cases.y <10)
		{
			/* je regarde autour s'il y a un rouge_ch_H ou un rouge_ch_B ou les 2. */
			
			if (cases.x >0 && plateau[(cases.x) -1][cases.y] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1);
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.x >0 && plateau[(cases.x) -1][cases.y] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1);
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
			
	
			if (cases.x <10 && plateau[(cases.x) +1][cases.y] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1);
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.x <10 && plateau[(cases.x) +1][cases.y] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1);
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
						
			if (cases.y >0 && plateau[cases.x][(cases.y) -1] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.y >0 && plateau[cases.x][(cases.y) -1] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
			
			if (cases.y >0 && cases.x <10 && plateau[(cases.x)+1][(cases.y) -1] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.y >0 && cases.x <10 && plateau[(cases.x)+1][(cases.y) -1] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
			
			if (cases.y <10 && plateau[cases.x][(cases.y) +1] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.y <10 && plateau[cases.x][(cases.y) +1] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
			
			if (cases.x > 0 && cases.y < 10 && plateau[(cases.x)-1][(cases.y) +1] == rouge_ch_H)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_B)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_H;
			}
			if (cases.x > 0 && cases.y < 10 && plateau[(cases.x)-1][(cases.y) +1] == rouge_ch_B)
			{
				if (plateau[cases.x][cases.y] == rouge_ch_H)
				{
					*gagnant = jr;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= rouge_ch_B;
			}
			
			/* je propage */
			if (plateau[cases.x][cases.y] != rouge)
				propagation(plateau, cases, plateau[cases.x][cases.y], rouge);
		}
		
		*joueur = jb;
	}
	
	 /*******************************************************************/
	/********************   copie/colle ^^'  ***************************/
	else
	{
		plateau[cases.x][cases.y] = bleu;
		
		/* j'empile mon historique*/
		empile(historique, cases, *joueur);
		
		if (cases.x==10)
		{
			plateau[cases.x][cases.y] = bleu_ch_D;
			if (cases.x >0 && plateau[(cases.x)-1][cases.y]==bleu_ch_G)
			{
				*gagnant = jb;
				return(1) ;
			}
			if (cases.x>0 && cases.y <10 && plateau[(cases.x)-1][(cases.y)+1] ==bleu_ch_G)
			{
				*gagnant = jb;
				return(1) ;
			}
			
			propagation(plateau, cases, bleu_ch_D, bleu);
						
		}
		
		if (cases.x==0)
		{
			plateau[cases.x][cases.y] = bleu_ch_G;
			if (cases.x <10 && plateau[(cases.x)+1][cases.y]==bleu_ch_D)
			{
				*gagnant = jb;
				return(1) ;
			}
			if (cases.x < 10 && cases.y > 0 && plateau[(cases.x)+1][(cases.y)-1] == bleu_ch_D)
			{
				*gagnant = jb;
				return(1) ;
			}
			
			propagation(plateau, cases, bleu_ch_G, bleu);			
		}
		
		if (cases.x > 0 && cases.x <10)
		{
			/* je regarde autour s'il y a un bleu_ch_G ou un bleu_ch_D ou les 2. */
			
			if (cases.x >0 && plateau[(cases.x) -1][cases.y] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.x >0 && plateau[(cases.x) -1][cases.y] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
	
			if (cases.x <10 && plateau[(cases.x) +1][cases.y] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.x <10 && plateau[(cases.x) +1][cases.y] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
			
			if (cases.y >0 && plateau[cases.x][(cases.y) -1] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.y >0 && plateau[cases.x][(cases.y) -1] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
			
			if (cases.y >0 && cases.x <10 && plateau[(cases.x)+1][(cases.y) -1] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.y >0 && cases.x <10 && plateau[(cases.x)+1][(cases.y) -1] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
			
		
			if (cases.y <10 && plateau[cases.x][(cases.y) +1] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.y <10 && plateau[cases.x][(cases.y) +1] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
			if (cases.x > 0 && cases.y < 10 && plateau[(cases.x)-1][(cases.y) +1] == bleu_ch_G)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_D)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_G;
			}
			if (cases.x > 0 && cases.y < 10 && plateau[(cases.x)-1][(cases.y) +1] == bleu_ch_D)
			{
				if (plateau[cases.x][cases.y] == bleu_ch_G)
				{
					*gagnant = jb;
					return(1) ;
				}
				else
					plateau[cases.x][cases.y]= bleu_ch_D;
			}
			
			/* je propage */
			if (plateau[cases.x][cases.y] != bleu)
				propagation(plateau, cases, plateau[cases.x][cases.y], bleu);
		}
		
		*joueur = jr;
	}

	return(0);
}

