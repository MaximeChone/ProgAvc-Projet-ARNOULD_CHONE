#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include "fonction.h"
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
			carte[i/17][i%17].c.y = (i/17)*48;
			carte[i/17][i%17].c.x = (i%17)*48;
			carte[i/17][i%17].tr.c.y = (i/17)*48;
			carte[i/17][i%17].tr.c.x = (i%17)*48;
		}
  	fclose(fichier);
}

void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen)
{

	SDL_Rect position;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i< 17 ; i++)
		{
			for (int j = 0; j<17 ; j++)
				{
						position.x = carte[i][j].c.x;
						position.y = carte[i][j].c.y;
						if (carte[i][j].type == 0)
							temp = 0;
						if (carte[i][j].type == 1)
							temp = 1;
						if (carte[i][j].type == 2)
							temp = 2;
						if (carte[i][j].type == 3)
							temp = 3;
						if (carte[i][j].type == 4)
							temp = 4;
						if (carte[i][j].type == 5)
							temp = 5;
				       	SDL_BlitSurface(TabImageCase[temp], NULL, screen, &position);

				}
		}

}


int sous_verifchemin_1(cm **carte,int i , int j)
{
	return ((carte[i-1][j].type == 2 || carte[i-1][j].type == 4 || carte[i-1][j].type == 5) && (carte[i+1][j].type == 2 || carte[i+1][j].type == 4 || carte[i+1][j].type == 5) && (carte[i][j-1].type != 2 && carte[i][j-1].type != 4 && carte[i][j-1].type != 5) && (carte[i][j+1].type != 2 && carte[i][j+1].type != 4 && carte[i][j+1].type != 5));
}
	
int sous_verifchemin_2(cm **carte, int i , int j)
{
	return ((carte[i][j+1].type == 2 || carte[i][j+1].type == 4 || carte[i][j+1].type == 5) && (carte[i][j-1].type == 2 || carte[i][j-1].type == 4 || carte[i][j-1].type == 5) && (carte[i+1][j].type != 2 && carte[i+1][j].type != 4 && carte[i+1][j].type != 5) && (carte[i-1][j].type != 2 && carte[i-1][j].type != 4 && carte[i-1][j].type != 5));
}

int sous_verifchemin_3(cm **carte,int i ,int j)
{
	return ((carte[i-1][j].type == 2 || carte[i-1][j].type == 4 || carte[i-1][j].type == 5) && (carte[i][j-1].type == 2 || carte[i][j-1].type == 4 || carte[i][j-1].type == 5) && (carte[i][j+1].type != 2 && carte[i][j+1].type != 4 && carte[i][j+1].type != 5) && (carte[i+1][j].type != 2 && carte[i+1][j].type != 4 && carte[i+1][j].type != 5) && (carte[i-1][j-1].type != 2 && carte[i-1][j-1].type != 4 && carte[i-1][j-1].type != 5));
}

int sous_verifchemin_4(cm **carte, int i , int j)
{
	return ((carte[i+1][j].type == 2 || carte[i+1][j].type == 4 || carte[i+1][j].type == 5) && (carte[i][j-1].type == 2 || carte[i][j-1].type == 4 || carte[i][j-1].type == 5) && (carte[i][j+1].type != 2 && carte[i][j+1].type != 4 && carte[i][j+1].type != 5) && (carte[i-1][j].type != 2 && carte[i-1][j].type != 4 && carte[i-1][j].type != 5) && (carte[i+1][j-1].type != 2 && carte[i+1][j-1].type != 4 && carte[i+1][j-1].type != 5));
}

int sous_verifchemin_5(cm **carte , int i ,int j)
{
return ((carte[i+1][j].type == 2 || carte[i+1][j].type == 4 || carte[i+1][j].type == 5) && (carte[i][j+1].type == 2 || carte[i][j+1].type == 4 || carte[i][j+1].type == 5) && (carte[i][j-1].type != 2 && carte[i][j-1].type != 4 && carte[i][j-1].type != 5) && (carte[i-1][j].type != 2 && carte[i-1][j].type != 4 && carte[i-1][j].type != 5) && (carte[i+1][j+1].type != 2 && carte[i+1][j+1].type != 4 && carte[i+1][j+1].type != 5));
}

int sous_verifchemin_6(cm **carte, int i ,int j)
{
return ((carte[i-1][j].type == 2 || carte[i-1][j].type == 4 || carte[i-1][j].type == 5) && (carte[i][j+1].type == 2 || carte[i][j+1].type == 4 || carte[i][j+1].type == 5) && (carte[i][j-1].type != 2 && carte[i][j-1].type != 4 && carte[i][j-1].type != 5) && (carte[i+1][j].type != 2 && carte[i+1][j].type != 4 && carte[i+1][j].type != 5) && (carte[i-1][j+1].type != 2 && carte[i-1][j+1].type != 4 && carte[i-1][j+1].type != 5));
}

int verifChemin(cm **carte)
{
	int d , f , i , j;
	for (i = 0 ; i <17 ; i++)
		{
			if (carte[i][0].type != 3)
				return 0;
			if (carte[i][16].type != 3)
				return 0;
			if (carte[0][i].type != 3)
				return 0;
			if (carte[16][i].type != 3)
				return 0;
		}
	f = 0;
	d = 0;
	for (i = 1 ; i < 16 ; i++)
		{
			for (j = 1 ; j< 16 ; j++)
				{
					if (carte[i][j].type == 4)
						{
							if (!(((carte[i-1][j].type == 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type == 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type == 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type == 2)) && d == 0))
								{
									return 0;
								}
							else 
								{
									d = 1;
								}
						}
					if (carte[i][j].type == 5)
						{
							if (carte[i-1][j].type == 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2)
								{
								}
							if (carte[i-1][j].type != 2 && carte[i+1][j].type == 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2)
								{
								}
							if (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type == 2 && carte[i][j-1].type != 2)
								{
								}
							if (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type == 2)
								{
								}
							if (!(((carte[i-1][j].type == 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type == 2 && carte[i][j+1].type != 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type == 2 && carte[i][j-1].type != 2) || (carte[i-1][j].type != 2 && carte[i+1][j].type != 2 && carte[i][j+1].type != 2 && carte[i][j-1].type == 2)) && f == 0))
								{
									return 0;
								}
							else 
								{
									f = 1;
								}
						}
					if (carte[i][j].type == 2)
						{
							if (!(sous_verifchemin_1(carte , i , j) || sous_verifchemin_2(carte, i , j) ||	sous_verifchemin_3(carte, i , j) || sous_verifchemin_4(carte, i , j) || sous_verifchemin_5(carte, i , j) || sous_verifchemin_6(carte, i , j)))
								{
									return 0;
								}
						}
				}
		}
							
	return 1;
}

void ini_chemin(coor *chemin)
{
	for (int i = 0 ; i<127 ; i++)
		{
			chemin[i].x = -1;
			chemin[i].y = -1;
		}
}

int emplacementDebut(cm **carte)
{
	for (int i=0 ; i<17 ; i++)
		{
			for (int j = 0;j<17 ; j++)
				{
					if (carte[i][j].type == 4)
						return 17*i + j;
				}
		}
	return 0;
}

void defchemin(cm **carte , int i , int j , char sens , coor *chemin , int compteurChemin)
{	
	if (carte[i][j].type == 4)
		{


			if (carte[i-1][j].type == 2)
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i-1 ,j , 'b' , chemin , compteurChemin + 1);
				}
			if (carte[i+1][j].type == 2)
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i+1 ,j , 'h' , chemin , compteurChemin + 1);
				}
			if (carte[i][j-1].type == 2)
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i ,j-1 , 'd' , chemin , compteurChemin + 1);
				}
			if (carte[i][j+1].type == 2)
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i ,j+1 , 'g' , chemin , compteurChemin + 1);
				}
		}
	if (carte[i][j].type == 5)
		{
			chemin[compteurChemin].x = carte[i][j].c.x;
			chemin[compteurChemin].y = carte[i][j].c.y;
		}
	if (carte[i][j].type == 2)
		{

			if ((carte[i-1][j].type == 2 || carte[i-1][j].type == 5) && sens != 'h')
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i-1 ,j , 'b' , chemin , compteurChemin + 1);
				}
			if ((carte[i+1][j].type == 2 || carte[i+1][j].type == 5) && sens !='b')
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i+1 ,j , 'h' , chemin , compteurChemin + 1);
				}
			if ((carte[i][j-1].type == 2 || carte[i][j-1].type == 5) && sens !='g')
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i ,j-1 , 'd' , chemin , compteurChemin + 1);
				}
			if ((carte[i][j+1].type == 2 || carte[i][j+1].type == 5) && sens != 'd')
				{
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte , i , j+1 , 'g' , chemin , compteurChemin +1);
				}
		}
}

void evenement_clavier(char* keys,int *gameover)
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			*gameover = 1;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				*gameover = 1;
				break;
			default:
				break;
			}
			keys[event.key.keysym.sym] = 1;
			break;
		}
	}
		
}

void evenement_verifClavier(char* key, int *d)
{
	SDLKey tabkey[2] = {SDLK_LEFT,SDLK_RIGHT}; 
	
	for(int i=0;i<1;i++)
		{
			if (key[tabkey[0]] == 1)
				{
					*d = *d-1;
					if (*d < 1)
						{
							*d = 1;
						}
				}
			if (key[tabkey[1]] == 1)
				{
					*d = *d + 1;
					if (*d > 100)
						{
							*d =100;
						}
				}
						
		}
}

void init_ennemis(enn *ennemis)
{
	for (int i=0 ; i< 200 ; i++)
	{
	    ennemis[i].active = 0;
	    ennemis[i].c.x = -1;
	    ennemis[i].c.y = -1;
	}
}
	  
void ennemi_moove(enn *ennemi , coor *chemin)
{
	if (ennemi->c.x == chemin[ennemi->chem+1].x)
	{
		if (ennemi->c.y < chemin[ennemi->chem + 1].y)
		{

			ennemi->c.y =ennemi->c.y + ennemi->v;
			anim_ennemi_bas(ennemi);
		}
		else
		{
		if (ennemi->c.y > chemin[ennemi->chem+1].y)
		{
			ennemi->c.y -= ennemi->v;
			anim_ennemi_haut(ennemi);
		}
		}
	}
	else
	{

	if (ennemi->c.y == chemin[ennemi->chem+1].y)
	{

		if (ennemi->c.x < chemin[ennemi->chem + 1].x)
		{

			ennemi->c.x += ennemi->v;
			anim_ennemi_droite(ennemi);
		}
		else
		{
		if (ennemi->c.x > chemin[ennemi->chem+1].x)
		{
			ennemi->c.x -= ennemi->v;
			anim_ennemi_gauche(ennemi);
		}
		}
	}
	}
	if ((ennemi->c.x == chemin[ennemi->chem+1].x) && (ennemi->c.y == chemin[ennemi->chem+1].y))
		ennemi->chem += 1;
}

void ennemis_moove(enn *ennemis , coor *chemin)
{
	for (int i = 0; i < 200 ; i++)
		{
			if (ennemis[i].active == 1)
				{
					ennemi_moove(&ennemis[i] , chemin);
				}
		}
}

void affichage_ennemi(enn *ennemis , SDL_Surface **tab_image_ennemis , SDL_Surface *screen)
{

	SDL_Rect position;
	SDL_Rect image;
	int colorkey;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i < 200 ; i++)
		{
			if (ennemis[i].active == 1)
			{
				position.x = ennemis[i].c.x;
				position.y = ennemis[i].c.y;
				image.y = 0;
				image.w = 48;
				image.h = 48;
				image.x = 48 * ennemis[i].anim;
				colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
				if (ennemis[i].type == 0)
					temp = 0;
				if (ennemis[i].type == 1)
					temp = 1;
				SDL_SetColorKey(tab_image_ennemis[temp], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			   	SDL_BlitSurface(tab_image_ennemis[temp], &image, screen, &position);

			}
		}

}

void anim_ennemi_haut(enn *ennemi)
{
	if (ennemi->anim == 4)
	{
		ennemi->anim += 1;
	}
	else
	{
		ennemi->anim = 4;
	}
}

void anim_ennemi_bas(enn *ennemi)
{
	if (ennemi->anim == 0)
	{
		ennemi->anim += 1;
	}
	else
	{
		ennemi->anim = 0;
	}
}

void anim_ennemi_droite(enn *ennemi)
{
	if (ennemi->anim == 2)
	{
		ennemi->anim += 1;
	}
	else
	{
		ennemi->anim = 2;
	}
}

void anim_ennemi_gauche(enn *ennemi)
{
	if (ennemi->anim == 6)
	{
		ennemi->anim += 1;
	}
	else
	{
		ennemi->anim = 6;
	}
}

void spawn_soldat(enn *ennemis , coor lieu)
{
	int i = 0;
	while (i > 200 || ennemis[i].active != 0)
	{
		i++;
	}
	ennemis[i].active = 1;
	ennemis[i].type = 0;
	ennemis[i].c.x = lieu.x;
	ennemis[i].c.y = lieu.y;
	ennemis[i].anim = 0;
	ennemis[i].chem = 0;
	ennemis[i].v = 2;
	ennemis[i].pv = 1;
	ennemis[i].pa = 0;
}

void spawn_tour(tower *tour)
{
	tour->active = 1;
	tour->dmg = 1;
	tour->level = 1;
}

void affichage_tour(SDL_Surface **tab_image_tour , cm **carte , SDL_Surface *screen)
{
	SDL_Rect position;
	SDL_Rect image;
	int colorkey;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 1; i > 16 ; i++)
		{
			for (int j = 1 ; i > 16 ; j++)
				{
						if (carte[i][j].tr.active == 1)
						{
							position.x = carte[i][j].c.x;
							position.y = carte[i][j].c.y;
							image.y = 0;
							image.w = 48;
							image.h = 48;
							image.x = 48;
							colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
							temp = 0;
							SDL_SetColorKey(tab_image_tour[temp], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
						   	SDL_BlitSurface(tab_image_tour[temp], &image, screen, &position);
						}
				}
		}
}


