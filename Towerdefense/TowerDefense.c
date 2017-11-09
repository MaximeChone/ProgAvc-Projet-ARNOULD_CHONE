#include <SDL.h>
#include <math.h>
#include "fonction.h"
#define PI 3.14159265358979323846

int main()
{
	int i;
	int gameover = 0;
	SDL_Surface *screen;
	SDL_Surface *TabImageCase[6];
	int d = 1;
	char key[SDLK_LAST] = {0};

	coor chemin[127];
	ini_chemin(chemin);
	
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

	int possible_chemin = verifChemin(carte);

	defchemin(carte , emplacementDebut(carte)/17 , emplacementDebut(carte)%17 ,'e',chemin ,0);

	while (gameover != 1 && possible_chemin == 1)
		{
			evenement_clavier(key,&gameover);
			evenement_verifClavier(key,&d);
			afficheMap(TabImageCase ,carte , screen);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(d);
			printf("%d\n",d);
		}

	i = 0;
	while (chemin[i].x != -1)
		{
			printf("%d : x = %d , y = %d\n",i,chemin[i].x,chemin[i].y);
			i = i+ 1 ;
		}


	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);
	SDL_FreeSurface(screen);

	return EXIT_SUCCESS;
}
	
