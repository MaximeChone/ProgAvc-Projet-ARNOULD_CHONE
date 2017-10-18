#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include "struct.h"
#define PI 3.14159265358979323846

void lectureNiveau(cm **carte)
{
	int tab1[17*17];
	FILE* fichier = fopen("niveau", "r");
	int i = 0;
	int t = fgetc(fichier);
	tab1[i] = t;
	while (t != EOF)
		{
			t = fgetc(fichier);
			if (t !=10)
				{
					i++;
					tab1[i]= t;
				}
		}
	for (i=0 ; i<17*17 ; i++)
		{
			//Determine le type des cases
			if (tab1[i] == 101)		
				carte[i/17][i%17].type = 3;
			if (tab1[i] == 100)
				carte[i/17][i%17].type = 4;
			if (tab1[i] == 99)
				carte[i/17][i%17].type = 2;
			if (tab1[i] == 109)
				carte[i/17][i%17].type = 1;
			if (tab1[i] == 102)
				carte[i/17][i%17].type = 5;
			if (tab1[i] == 104)
				carte[i/17][i%17].type = 0;
			//Détermine les positions des cases et des tours
			carte[i/17][i%17].tr.active = 0;
			carte[i/17][i%17].y = (i/17)*48;
			carte[i/17][i%17].x = (i%17)*48;
			carte[i/17][i%17].tr.y = (i%17)*48;
			carte[i/17][i%17].tr.x = (i%17)*48;
		}
      	fclose(fichier);
}

void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen)
{
	SDL_Surface *image;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i< 17 ; i++)
		{
			for (int j = 0; j<17 ; j++)
				{
						position.x = carte[i][j].x;
						position.y = carte[i][j].y;
						if (carte[i][j].type == 0)
							image = TabImageCase[0];
						if (carte[i][j].type == 1)
							image = TabImageCase[1];
						if (carte[i][j].type == 2)
							image = TabImageCase[2];
						if (carte[i][j].type == 3)
							image = TabImageCase[3];
						if (carte[i][j].type == 4)
							image = TabImageCase[4];
						if (carte[i][j].type == 5)
							image = TabImageCase[5];
						SDL_BlitSurface(image, NULL, screen, &position);
				}
		}
	SDL_FreeSurface(image);
}
				
