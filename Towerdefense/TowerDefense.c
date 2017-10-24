#include <SDL.h>
#include <math.h>
#include "fonction.h"
#define PI 3.14159265358979323846

int main()
{
	int i;
	int gameover = 0;
	SDL_Surface *screen , *image ;
	SDL_Surface *TabImageCase[6];
	int d = 1;
	char key[SDLK_LAST] = {0};
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_WM_SetCaption("Tower Defense", "Tower Defense");
	
	screen = SDL_SetVideoMode(816 ,816 , 0, 0);



	TabImageCase[0]=SDL_DisplayFormat(SDL_LoadBMP("herbe.bmp"));
	TabImageCase[1]=SDL_DisplayFormat(SDL_LoadBMP("montagne.bmp"));
	TabImageCase[2]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	TabImageCase[3]=SDL_DisplayFormat(SDL_LoadBMP("eau.bmp"));
	TabImageCase[4]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	TabImageCase[5]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	image = TabImageCase[0];
	

	cm **carte = malloc(sizeof(struct case_map*) *17);

	for (i=0 ; i <17; i++)
		carte[i] = malloc(sizeof(struct case_map) * 17);
 
	lectureNiveau(carte);
	int chemin = verifChemin(carte);
	while (gameover != 1 && chemin == 1)
		{
			evenement_clavier(key,&gameover);
			evenement_verifClavier(key,&d);
			afficheMap(TabImageCase ,carte , screen , image);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(d);
			printf("%d\n");
		}



	printf("%d\n",chemin);


	
	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);
	SDL_FreeSurface(image);
	SDL_FreeSurface(screen);

	return EXIT_SUCCESS;
}
	
