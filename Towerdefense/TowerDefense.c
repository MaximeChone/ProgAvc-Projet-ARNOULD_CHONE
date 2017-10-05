#include <SDL.h>
#include <math.h>
#include "fonction.c"
#define PI 3.14159265358979323846

int main()
{
	cm **tab = malloc(sizeof(*tab) *17);
	int i;
	SDL_Surface *screen , *temp,*herbe;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	for (i=0 ; i <17; i++)
		tab[i] = malloc(sizeof(**tab) * 17);


	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Tower Defense", "Tower Defense");
	screen = SDL_SetVideoMode(816 ,816 , 0, 0);
	temp  = SDL_LoadBMP("sprite_herbe.bmp");
	herbe = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	for (i=0 ; i<17 ; i++)
		for (int j=0 ; j<17 ; j++)
			{
				position.x = i*48;
				position.y = j*48;
				SDL_BlitSurface(herbe, NULL, screen, &position);
			}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	sleep(1);
	free(*tab);
	SDL_FreeSurface(screen);

	return EXIT_SUCCESS;
}
	
