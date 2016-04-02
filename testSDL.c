#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,"Erreur SDL : %s\n",SDL_GetError());
	}
	/* Surface principale */
	SDL_Surface *fenetre = NULL;
	/* Boucle */
	while(1) {
		fenetre = SDL_SetVideoMode(500,500,32,SDL_HWSURFACE);
	}	
	SDL_FreeSurface(fenetre);
	/* on quitte et vide la mémoire */	
	SDL_Quit(); 
	return 0;
}
