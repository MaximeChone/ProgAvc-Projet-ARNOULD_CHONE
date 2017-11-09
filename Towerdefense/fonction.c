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
	printf("%d\n",compteurChemin);
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
			printf("f\n");
			chemin[compteurChemin].x = carte[i][j].c.x;
			chemin[compteurChemin].y = carte[i][j].c.y;
		}
	if (carte[i][j].type == 2)
		{

			if ((carte[i-1][j].type == 2 || carte[i-1][j].type == 5) && sens != 'h')
				{
					printf("c1\n");
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i-1 ,j , 'b' , chemin , compteurChemin + 1);
				}
			if ((carte[i+1][j].type == 2 || carte[i+1][j].type == 5) && sens !='b')
				{
					printf("c2\n");
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i+1 ,j , 'h' , chemin , compteurChemin + 1);
				}
			if ((carte[i][j-1].type == 2 || carte[i][j-1].type == 5) && sens !='g')
				{
					printf("c3\n");
					chemin[compteurChemin].x = carte[i][j].c.x;
					chemin[compteurChemin].y = carte[i][j].c.y;
					defchemin(carte ,i ,j-1 , 'd' , chemin , compteurChemin + 1);
				}
			if ((carte[i][j+1].type == 2 || carte[i][j+1].type == 5) && sens != 'd')
				{
					printf("c4\n");
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
					if (*d < 0)
						{
							*d = 0;
						}
				}
			if (key[tabkey[1]] == 1)
				{
					*d = *d + 1;
					if (*d > 30)
						{
							*d = 30;
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
	  














				
