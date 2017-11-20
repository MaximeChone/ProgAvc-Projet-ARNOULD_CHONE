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
			carte[i/17][i%17].c.y = (i/17)*48;
			carte[i/17][i%17].c.x = (i%17)*48;
			carte[i/17][i%17].tr.c.y = (i/17)*48;
			carte[i/17][i%17].tr.c.x = (i%17)*48;
			carte[i/17][i%17].tr.active = 0;
			carte[i/17][i%17].anim = 0;
			carte[i/17][i%17].taille_sprite = 48;
		
		}
  	fclose(fichier);
}

void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen)
{

	SDL_Rect position;
	SDL_Rect image;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i< 17 ; i++)
		{
			for (int j = 0; j<17 ; j++)
				{
						if (carte[i][j].type == 4 || carte[i][j].type == 5)
						{
							carte[i][j].anim += 1;
							if (carte[i][j].anim > 3)
								{
									carte[i][j].anim = 0;
								}						
						}
						
						position.x = carte[i][j].c.x;
						position.y = carte[i][j].c.y;
						image.y = 0;
						image.h = carte[i][j].taille_sprite;
						image.w = carte[i][j].taille_sprite;
						image.x = carte[i][j].taille_sprite * carte[i][j].anim;
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
				       	SDL_BlitSurface(TabImageCase[temp], &image, screen, &position);

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

int emplacementFin(cm **carte)
{
	for (int i=0 ; i<17 ; i++)
		{
			for (int j = 0;j<17 ; j++)
				{
					if (carte[i][j].type == 5)
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
					*d = *d-2;
					if (*d < 1)
						{
							*d = 1;
						}
				}
			if (key[tabkey[1]] == 1)
				{
					*d = *d + 2;
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
				image.w = ennemis[i].taille_sprite;
				image.h = ennemis[i].taille_sprite;
				image.x = ennemis[i].taille_sprite * ennemis[i].anim;
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
	while (i < 200 && ennemis[i].active != 0)
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
	ennemis[i].pv = 50;
	ennemis[i].pa = 0;
	ennemis[i].taille_sprite = 48;
}

void spawn_tour_lvl_1(tower *tour)
{
	tour->active = 1;
	tour->dmg = 1;
	tour->level = 1;
	tour->taille_sprite = 48;
	tour->anim = 0;
	tour->range = 200;
	tour->cooldown = 20;
}

void affichage_tour(SDL_Surface **tab_image_tour , cm **carte , SDL_Surface *screen)
{
	SDL_Rect position;
	SDL_Rect image;
	int colorkey;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 1; i < 16 ; i++)
		{
			for (int j = 1 ; j < 16 ; j++)
				{
						if (carte[i][j].tr.active == 1)
						{
							position.x = carte[i][j].tr.c.x;
							position.y = carte[i][j].tr.c.y;
							image.y = 0;
							image.w = carte[i][j].tr.taille_sprite;
							image.h = carte[i][j].tr.taille_sprite;
							image.x = carte[i][j].tr.anim * carte[i][j].tr.taille_sprite;
							colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
							temp = 0;
							SDL_SetColorKey(tab_image_tour[temp], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
						   	SDL_BlitSurface(tab_image_tour[temp], &image, screen, &position);
						}
				}
		}
}

void init_tirs(sh *tirs)
{
  for (int i = 0 ; i < 500 ; i++)
  {
      tirs[i].active = 0;
  }
}

void spawn_tir(sh *tirs , int cible , tower *tour)
{
  int i=0;
  while (i < 500 && tirs[i].active != 0)
  {
	  i++;
  }
	tirs[i].active = 1;
	tirs[i].c.x = tour->c.x;
	tirs[i].c.y = tour->c.y;
	tirs[i].cible = cible;
	tirs[i].v = 3;
	tirs[i].dmg = tour->dmg;
	tirs[i].taille_sprite = 8;
	tour->timer = 0;
}

void supp_tour(tower *tour)
{
  tour->active = 0;
  tour->dmg = 0;
  tour->level = 0;
tour->anim = 0;
tour->taille_sprite = 0;
}

void supp_ennemi(enn *ennemi)
{
  ennemi->active = 0;
  ennemi->type = 0;
  ennemi->c.x = 0;
  ennemi->c.y = 0;
  ennemi->anim = 0;
  ennemi->chem = 0;
  ennemi->v = 0;
  ennemi->pv = 0;
  ennemi->pa = 0;
	ennemi->taille_sprite = 0;
}

void supp_tir(sh *tir)
{
	tir->active = 0;
	tir->c.x = 0;
	tir->c.y = 0;
	tir->cible = 0;
	tir->v = 0;
	tir->dmg = 0;
	tir->anim = 0;
	tir->taille_sprite = 0;
}

void tir_moove(sh *tir , enn *ennemis)
{
	if (ennemis[tir->cible].active == 0)
		supp_tir(tir);
	float angle = (atan2((ennemis[tir->cible].c.y + ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2) - (tir->c.y),(ennemis[tir->cible].c.x+ ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2) - (tir->c.x) )/PI)*180;
 	angle = 0 - angle;
	if (angle < 0 )
		angle += 360;
	tir->c.x += tir->v*(cos(PI * ((angle)/180.0)));
	tir->c.y += tir->v*(-sin(PI * ((angle)/180.0)));
	if ((fabs(tir->c.x - (ennemis[tir->cible].c.x+ ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2)) <= tir->v) && (fabs(tir->c.y - (ennemis[tir->cible].c.y + ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2)) <= tir->v))
		{
			damage(tir->dmg , &ennemis[tir->cible]);
			supp_tir(tir);
		}
}

void tirs_moove(sh *tirs , enn *ennemis)
{
	for (int i = 0; i < 500 ; i++)
		{
			if (tirs[i].active == 1)
				{
					tir_moove(&tirs[i] , ennemis);
				}
		}
}
void affichage_tir(SDL_Surface **tab_image_tir , sh *tir , SDL_Surface *screen)
{

	SDL_Rect position;
	SDL_Rect image;
	int colorkey;
	int temp;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i < 500 ; i++)
		{
			if (tir[i].active == 1)
			{
				position.x = tir[i].c.x;
				position.y = tir[i].c.y;
				image.y = 0;
				image.w = tir[i].taille_sprite;
				image.h = tir[i].taille_sprite;
				image.x = tir[i].taille_sprite * tir[i].anim;
				colorkey = SDL_MapRGB(screen->format, 255, 126, 0);
				temp = 0;
				SDL_SetColorKey(tab_image_tir[temp], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			   	SDL_BlitSurface(tab_image_tir[temp], &image, screen, &position);

			}
		}

}

void damage(int dmg , enn *ennemi)
{
	dmg -= ennemi->pa;
	if (dmg > 0)
		ennemi->pv -= dmg;
}

void check_vie(enn *ennemis)
{
	for (int i = 0 ; i < 200 ; i++)
	{
		if(ennemis[i].active == 1 && ennemis[i].pv <= 0)
		{
			supp_ennemi(&ennemis[i]);
		}
	}
}

void check_range(cm **carte , enn *ennemis , sh *tirs)
{
	for (int i = 1 ; i < 16 ; i++)
	{
		for (int j = 1 ; j < 16 ; j++)
		{
			if (carte[i][j].tr.active == 1)
			{
				for (int x = 0 ; x < 200 ; x++)
				{
					if (ennemis[x].active == 1)
					{
						if (sqrt(pow(carte[i][j].tr.c.x - ennemis[x].c.x, 2) + pow(carte[i][j].tr.c.y - ennemis[x].c.y, 2)) <= carte[i][j].tr.range)
						{
							if (carte[i][j].tr.timer >= carte[i][j].tr.cooldown)
							{
								spawn_tir(tirs ,x , &carte[i][j].tr);
							}
						}
					}
				}
			}
		}
	}
}

void timer_tours(cm **carte)
{
	for (int i = 1 ; i < 16 ; i++)
	{
		for (int j = 1 ; j < 16 ; j++)
		{
			carte[i][j].tr.timer += 1;
		}
	}
}
