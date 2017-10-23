#include <SDL.h>
#include <math.h>
#include "fonction.h"
#define PI 3.14159265358979323846

int main()
{
	int i;
	SDL_Surface *screen;
	SDL_Surface *TabImageCase[6];

	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_WM_SetCaption("Tower Defense", "Tower Defense");
	
	screen = SDL_SetVideoMode(816 ,816 , 0, 0);



	TabImageCase[0]=SDL_DisplayFormat(SDL_LoadBMP("herbe.bmp"));
	TabImageCase[1]=SDL_DisplayFormat(SDL_LoadBMP("montagne.bmp"));
	TabImageCase[2]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	TabImageCase[3]=SDL_DisplayFormat(SDL_LoadBMP("eau.bmp"));
	TabImageCase[4]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	TabImageCase[5]=SDL_DisplayFormat(SDL_LoadBMP("chemin.bmp"));
	
	cm **carte = malloc(sizeof(struct case_map*) *17);

	for (i=0 ; i <17; i++)
		carte[i] = malloc(sizeof(struct case_map) * 17);
    
	lectureNiveau(carte);
	afficheMap(TabImageCase ,carte , screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	int testfunction = verifChemin(carte);
	printf("%d\n",testfunction);

	sleep(3);



	
	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);		
	SDL_FreeSurface(screen);

	return EXIT_SUCCESS;
}
	
