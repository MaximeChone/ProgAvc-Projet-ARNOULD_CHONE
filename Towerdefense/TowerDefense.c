#include <SDL.h>
#include <math.h>
#include "fonction.c"
#define PI 3.14159265358979323846

int main()
{
	int i,j;
	SDL_Surface *screen;
    SDL_Surface *TabImageCase[6];

	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetCaption("Tower Defense", "Tower Defense");

	screen = SDL_SetVideoMode(816 ,816 , 0, 0);



    TabImageCase[0]=SDL_DisplayFormat(SDL_LoadBMP("sprite_herbe.bmp"));
    TabImageCase[1]=SDL_DisplayFormat(SDL_LoadBMP("sprite_montagne.bmp"));
    TabImageCase[2]=SDL_DisplayFormat(SDL_LoadBMP("sprite_chemin.bmp"));
    TabImageCase[3]=SDL_DisplayFormat(SDL_LoadBMP("sprite_eau.bmp"));
    TabImageCase[4]=SDL_DisplayFormat(SDL_LoadBMP("sprite_chemin.bmp"));
    TabImageCase[5]=SDL_DisplayFormat(SDL_LoadBMP("sprite_chemin.bmp"));

	cm **carte = malloc(sizeof(carte) *17);

	for (i=0 ; i <17; i++)
		carte[i] = malloc(sizeof(*carte) * 17);

	lectureNiveau(carte);
	for (int i = 0; i< 17 ; i++)
			for (int j = 0; j<17 ; j++)
					printf("type : %d\n",carte[i][j].type);


	afficheMap(TabImageCase ,carte , screen);





	SDL_UpdateRect(screen, 0, 0, 0, 0);

	sleep(3);





	for (i=0 ; i <17; i++)
	free(carte[i]);
	free(carte);
	SDL_FreeSurface(*TabImageCase);
	SDL_FreeSurface(screen);

	return EXIT_SUCCESS;
}
	
