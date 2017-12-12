#include "fonction.h"

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
			carte[i/17][i%17].tr.level = -1;
			carte[i/17][i%17].tr.amelio = prix_amelio(-1);
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

void evenement_clavier(char* keys,int *gameover,coor *cursor , cm **select , cm **carte , int *devise , int *pause , int *exit)
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		/*case SDL_QUIT:
			*gameover = 1;
			break;*/
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_p:
				if (*pause == 1)
				{
					*pause = 0;
				}
				else
				{
					*pause = 1;
				}
			break;
			case SDLK_ESCAPE:
				if (*gameover == 0)
				{
					*gameover = 1;
				}
				else
				{
					*exit = 1;
					*gameover = 0;
				}
				break;
			default:
				break;
			}
			keys[event.key.keysym.sym] = 1;
				break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button){
			case SDL_BUTTON_LEFT:
				if (*pause == 0 && *gameover == 0)
				{
					if (event.button.x <= 816 && event.button.y <=816)
					{
						selection(carte , event.button.x , event.button.y , select);
					}
					clic_gauche(*cursor , *select , devise);
				}
				break;
			case SDL_BUTTON_RIGHT:
				deselection(select);
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			cursor->x = event.motion.x;
			cursor->y = event.motion.y;
			break;
		}
	}
}

void evenement_verifClavier(char* key, int *d)
{
	SDLKey tabkey[4] = {SDLK_LEFT,SDLK_RIGHT,SDLK_UP}; 
	
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
			if (key[tabkey[2]] == 1)
			{
			}
		}
}

void init_ennemis(enn *ennemis)
{
	for (int i=0 ; i< 600 ; i++)
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
	for (int i = 0; i < 600 ; i++)
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
	for (int i = 0; i < 600 ; i++)
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
	if (ennemi->type == SOLDAT)
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
	if (ennemi->type == TANK)
	{
		ennemi->anim = 2;
	}
}

void anim_ennemi_bas(enn *ennemi)
{
	if (ennemi->type == SOLDAT)
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
	if (ennemi->type == TANK)
	{
		ennemi->anim = 0;
	}
}

void anim_ennemi_droite(enn *ennemi)
{
	if (ennemi->type == SOLDAT)
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
	if (ennemi->type == TANK)
	{
		ennemi->anim = 1;
	}
}

void anim_ennemi_gauche(enn *ennemi)
{

	if (ennemi->type == SOLDAT)
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
	if (ennemi->type == TANK)
	{
		ennemi->anim = 3;
	}
		
}


void spawn_soldat(enn *ennemis , coor lieu , int lvl)
{
	int i = 0;
	while (i < 600 && ennemis[i].active != 0)
	{
		i++;
	}
	ennemis[i].lvl = lvl;
	ennemis[i].active = 1;
	ennemis[i].type = SOLDAT;
	ennemis[i].c.x = lieu.x;
	ennemis[i].c.y = lieu.y;
	ennemis[i].anim = 0;
	ennemis[i].chem = 0;
	ennemis[i].v = 4;
	ennemis[i].pv = calc_pv_soldat(lvl)*2;
	ennemis[i].pv_max = calc_pv_soldat(lvl)*2;
	ennemis[i].pa = calc_pa_soldat(lvl);
	ennemis[i].taille_sprite = 48;
	ennemis[i].dmg = 1;
	ennemis[i].devise = gain_devise_soldat(lvl);
}

void spawn_tank(enn *ennemis , coor lieu , int lvl)
{
	int i = 0;
	while (i < 600 && ennemis[i].active != 0)
	{
		i++;
	}
	ennemis[i].lvl = lvl;
	ennemis[i].active = 1;
	ennemis[i].type = TANK;
	ennemis[i].c.x = lieu.x;
	ennemis[i].c.y = lieu.y;
	ennemis[i].anim = 0;
	ennemis[i].chem = 0;
	ennemis[i].v = 2;
	ennemis[i].pv = calc_pv_tank(lvl)*2;
	ennemis[i].pv_max = calc_pv_tank(lvl)*2;
	ennemis[i].pa = calc_pa_tank(lvl);
	ennemis[i].taille_sprite = 48;
	ennemis[i].dmg = 3;
	ennemis[i].devise = gain_devise_tank(lvl);
}
void spawn_tour_lvl_0(tower *tour)
{
	tour->type = B;
	tour->active = 1;
	tour->dmg = 2;
	tour->level = 0;
	tour->taille_sprite = 48;
	tour->anim = 0;
	tour->range = 180;
	tour->cooldown = 25;
	tour->amelio = prix_amelio(tour->level);
}

void spawn_tour_lvl_1(tower *tour , t_type type)
{
	if (tour->level == 0)
	{
	    tour->type = type;
	    if (type == P)
	    {
		tour->dmg = 8;
		tour->range = 205;
		tour->cooldown = 60;
	    }
	    if (type == V)
	    {
		tour->dmg = 2;
		tour->range = 155;
		tour->cooldown = 15;
	    } 
	    tour->level += 1;
		tour->type = type;
		tour->amelio = prix_amelio(tour->level);
	}
}

void spawn_tour_lvl_2(tower *tour , t_type type)
{
	if (tour->level == 1)
	{
		switch(tour->type){
		case P:
			if (type == P)
			{
				tour->type = P;
				tour->dmg = 16;
				tour->range = 205;
				tour->cooldown = 40;
			}
	    	if (type == V)
	    	{
				tour->type = H;
				tour->dmg =  8 ;
				tour->range = 180;
				tour->cooldown = 20;
			}
			break;
		case V:
			if (type == P)
			{
				tour->type = H;
				tour->dmg =  8 ;
				tour->range = 180;
				tour->cooldown = 20;
			}
	    	if (type == V)
	    	{
				tour->type = V;
				tour->dmg = 4;
				tour->range = 155;
				tour->cooldown = 10;
			}
			break;
		default:
			break;
	    }
	    tour->level += 1;
		tour->amelio = prix_amelio(tour->level);
	}
}

void spawn_tour_lvl_3(tower *tour , t_type type)
{
	if (tour->level == 2)
	{
	  switch(tour->type){
	    case P:
	      if (type == P)
	      {
		  tour->type = P;
		  tour->dmg = 32;
		  tour->range = 230;
		  tour->cooldown = 60;
	      }
	      if (type == V)
	      {	    
		  tour->type = HP;
		  tour->dmg = 16;
		  tour->range = 205;
		  tour->cooldown = 20;	    
	      }
	      break;
	    case V:
	      if (type == P)
	      {
		  tour->type = HV;
		  tour->dmg = 8;
		  tour->range = 155;
		  tour->cooldown = 10;
	      }
	      if (type == V)
	      {	    
		  tour->type = V;
		  tour->dmg = 8;
		  tour->range = 130;
		  tour->cooldown = 5;
	      }
	      break;
	    case H:
	      if (type == P)
	      {
		  tour->type = HP;
		  tour->dmg = 16;
		  tour->range = 205;
		  tour->cooldown = 20;	 
	      }
	      if (type == V)
	      {
		  tour->type = HV;
		  tour->dmg = 8;
		  tour->range = 155;
		  tour->cooldown = 10;
	      }
	      break;
	    default:
	      break;
	  }
		tour->level += 1;
		tour->amelio = 0;

	}
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
							switch(carte[i][j].tr.type)
							{
								case P:
									if (carte[i][j].tr.level == 1)
										temp = 1;
									if (carte[i][j].tr.level == 2)
										temp = 3;
									if (carte[i][j].tr.level == 3)
										temp = 6;
									break;
								case V:
									if (carte[i][j].tr.level == 1)
										temp = 2;
									if (carte[i][j].tr.level == 2)
										temp = 5;
									if (carte[i][j].tr.level == 3)
										temp = 9;
									break;
								case H:
									temp = 4;
									break;
								case HP:
									temp = 7;
									break;
								case HV:
									temp = 8;
									break;
								case B:
									temp = 0;
									break;
								default:
									temp = 0;
									break;
							}
									
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
	tirs[i].taille_sprite = 18;
	tirs[i].c.x = tour->c.x + tour->taille_sprite/2 - tirs[i].taille_sprite/2;
	tirs[i].c.y = tour->c.y + tour->taille_sprite/2 - tirs[i].taille_sprite/2;
	tirs[i].cible = cible;
	tirs[i].v = 5;
	tirs[i].dmg = tour->dmg;

	tour->timer = 0;
}

void supp_tour(tower *tour , int *devise)
{
    *devise += calcul_vente(tour->level);
	tour->type = 0;
	tour->level = -1; 
	tour->dmg = 0;
	tour->active = 0;
	tour->anim = 0;
	tour->range = 0;
	tour->cooldown = 0;
	tour->timer = 0;
	tour->amelio = 0;
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
	ennemi->pv_max = 0;
	ennemi->lvl = 0;
	ennemi->dmg = 0;
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

int calc_pv_soldat(int lvl)
{
	if (lvl <= 0)
		return 0;
	if (lvl == 1)
		return 4;
	return (calc_pv_soldat(lvl - 1)*3)/8 + calc_pv_soldat(lvl - 1);
}

int calc_pv_tank(int lvl)
{
	if (lvl == 10)
		return 3 + calc_pv_tank(lvl-1);
	if (lvl<= 0)
		return 0;
	if (lvl == 1)
		return 8;
	return (calc_pv_tank(lvl -1)*3)/8 + calc_pv_tank(lvl-1);
}

int calc_pa_tank(int lvl)
{
	if (lvl <= 1)
		return 0;
	if (lvl <= 4)
		return 2;
	if (lvl <= 8)
		return 4;
	return calc_pa_tank(lvl -1) + 1;
}

int calc_pa_soldat(int lvl)
{
	if (lvl <= 3)
		return 0;
	if (lvl <=5)
		return 1;
	if (lvl <= 7)
		return 2;
	if (lvl <= 10)
		return 3;
	return 0;
}

void tir_moove(sh *tir , enn *ennemis)
{
	if (ennemis[tir->cible].active == 0)
		supp_tir(tir);
	float angle = calcul_angle_tir(tir->c.x , tir->c.y , ennemis[tir->cible].c.x , ennemis[tir->cible].c.y , tir->taille_sprite , ennemis[tir->cible].taille_sprite);
	anim_tir(tir);
	tir->c.x += tir->v*(cos(PI * ((angle)/180.0)));
	tir->c.y += tir->v*(-sin(PI * ((angle)/180.0)));
	if (sqrt(pow(tir->c.x - (ennemis[tir->cible].c.x + ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2), 2) + pow(tir->c.y - (ennemis[tir->cible].c.y  + ennemis[tir->cible].taille_sprite/2 - tir->taille_sprite/2), 2)) <= tir->v)
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
				colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
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

void check_vie(enn *ennemis, int *devise)
{
	for (int i = 0 ; i < 600 ; i++)
	{
		if(ennemis[i].active == 1 && ennemis[i].pv <= 0)
		{
			*devise += ennemis[i].devise;
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
				for (int x = 0 ; x < 600 ; x++)
				{
					if (ennemis[x].active == 1)
					{
						if (sqrt(pow(carte[i][j].tr.c.x - ennemis[x].c.x, 2) + pow(carte[i][j].tr.c.y - ennemis[x].c.y, 2)) <= carte[i][j].tr.range)
						{
							if (check_tir_dmg_suffisant(ennemis , x , tirs) == 0 && check_tir_sup_pa(ennemis[x] , carte[i][j].tr) == 1)
							{
								float angle = calcul_angle_tour(carte[i][j].tr.c.x , carte[i][j].tr.c.y , ennemis[x].c.x , ennemis[x].c.y , carte[i][j].tr.taille_sprite , ennemis[x].taille_sprite);
								anim_tour(&carte[i][j].tr,angle);
								if (carte[i][j].tr.timer >= carte[i][j].tr.cooldown)
								{
									spawn_tir(tirs ,x , &carte[i][j].tr);
								}
							 	break;
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
			if (carte[i][j].tr.active == 1)
				{
					if (carte[i][j].tr.timer < carte[i][j].tr.cooldown)
						carte[i][j].tr.timer += 1;
				}
		}
	}
}

float calcul_angle_tour(float x1 , float y1 , float x2,float y2 , int sprite_taille_1 , int sprite_taille_2)
{
	float angle = (atan2((y2 + sprite_taille_2/2 ) - (y1 + sprite_taille_1/2),(x2 + sprite_taille_2/2 ) - (x1 + sprite_taille_1/2) )/PI)*180;
 	angle = 0 - angle;
	if (angle < 0 )
		angle += 360;
	return angle;
}

float calcul_angle_tir(float x1 , float y1 , float x2,float y2 , int sprite_taille_1 , int sprite_taille_2)
{
	float angle = (atan2((y2 + sprite_taille_2/2 - sprite_taille_1/2) - (y1),(x2 + sprite_taille_2/2 - sprite_taille_1/2) - (x1) )/PI)*180;
 	angle = 0 - angle;
	if (angle < 0 )
		angle += 360;
	return angle;
}

void anim_tour(tower *tour, float angle)
{
	angle += 5;
	if (angle >= 360)
		angle -= 360;
	angle = (int)angle;
	int anim = angle/10;
	tour->anim = anim;
}

void anim_tir(sh *tir)
{
	tir->anim += 1;
	if (tir->anim > 17)
		tir->anim = 0;
}

int check_tir_dmg_suffisant(enn *ennemis , int cible , sh *tirs)
{
	int dmg;
	int pa = ennemis[cible].pa;
	int pv = ennemis[cible].pv;
	for (int i = 0 ; i < 500 ; i++)
	{
		if (tirs[i].cible == cible && tirs[i].active == 1)
		{
			dmg = tirs[i].dmg;
			dmg -= pa;
			if (dmg < 0)
				dmg = 0;
			pv -= dmg;
		}
	}
	return pv <= 0;
}

int check_tir_sup_pa(enn ennemi , tower tour)
{
	return tour.dmg - ennemi.pa > 0;
}

void barre_vie_ennemi(enn ennemi , SDL_Surface *screen)
{
			double taille;
			SDL_Rect position;
			SDL_Surface *rectVi;
			taille = (ennemi.taille_sprite/2);
			rectVi = SDL_CreateRGBSurface(SDL_HWSURFACE, (int)taille , 4 , 32 , 0 , 0, 0, 0);
			SDL_FillRect(rectVi , NULL , SDL_MapRGB(screen->format, 255 , 0 , 0));
			position.x = ennemi.c.x + ennemi.taille_sprite/4;
			position.y = ennemi.c.y + 4;
			SDL_BlitSurface(rectVi, NULL, screen, &position);
			taille = ((float)ennemi.pv/ ennemi.pv_max) * (ennemi.taille_sprite/2);
			rectVi = SDL_CreateRGBSurface(SDL_HWSURFACE, (int)taille , 4 , 32 , 0 , 0, 0, 0);
			SDL_FillRect(rectVi , NULL , SDL_MapRGB(screen->format, 0 , 255 , 0));
			SDL_BlitSurface(rectVi, NULL, screen, &position);
			SDL_FreeSurface(rectVi);

		
}

void barre_vie_ennemis(enn *ennemis , SDL_Surface *screen)
{
	for (int i = 0 ; i < 600 ; i++)
	{
		if (ennemis[i].active == 1)
			barre_vie_ennemi(ennemis[i] , screen);
	}
}

void affichage_cursor(SDL_Surface *cursor_image , coor cursor , SDL_Surface *screen)
{
	SDL_Rect position;
	position.x = cursor.x;
	position.y = cursor.y;
	int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(cursor_image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_BlitSurface(cursor_image , NULL , screen , &position);
}

void selection(cm **carte, int x , int y , cm **select)
{
	int i ,j ;
	i = (int)y/48;
	j = (int)x/48;
	*(select) = &(carte[i][j]);
}

void deselection(cm **select)
{
	*(select) = NULL;
}

void ecrire_texte(TTF_Font *police , coor lieu , SDL_Surface *screen , char *texte ,SDL_Color color )
{
	SDL_Surface *image = TTF_RenderText_Blended(police , texte , color);
	SDL_Rect position;
	position.x = lieu.x;
	position.y = lieu.y;
	SDL_BlitSurface(image, NULL, screen, &position);
	SDL_FreeSurface(image);
}

void ecrire_info_case_select(cm *select , TTF_Font *police  , SDL_Surface *screen  ,SDL_Color vert , SDL_Color bleu , SDL_Color rouge ,int devise , SDL_Surface **tab_image_info , vague *vag , enn *ennemis , int num_vague , int pv_joueur)
{

	char text[100];
	SDL_Rect position;
	int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	coor lieu = {823 , 775};

	sprintf(text,"Devise : %d",devise);
	ecrire_texte(police , lieu , screen , text , vert);

	lieu.y = 795;
	sprintf(text,"Pv du JOUEUR : %d",pv_joueur);
	ecrire_texte(police , lieu , screen , text , rouge);
	if (num_vague != -1)
	{
		if (vag[num_vague].temps_avant_deb > 0)
		{
			lieu.y = 180;
			sprintf(text,"Preparation : %d",vag[num_vague].temps_avant_deb);
			ecrire_texte(police , lieu , screen ,text , vert);
		}
		lieu.y = 200;
		sprintf(text,"Vague : %d",num_vague + 1);
		ecrire_texte(police , lieu , screen ,text , vert);
	
		lieu.y = 220;
		sprintf(text,"Ennemis restants");
		ecrire_texte(police, lieu , screen ,text , vert);

		lieu.x = 833;
		lieu.y = 235;
		sprintf(text,"-Soldats : %d",nb_soldat_restant(ennemis , vag , num_vague));
		ecrire_texte(police, lieu , screen ,text , vert);

		lieu.y = 250;
		sprintf(text,"-TANK : %d",nb_tank_restant(ennemis , vag , num_vague));
		ecrire_texte(police, lieu , screen ,text , vert);
	}

	if (!(select == NULL))
	{
		lieu.x = 823;
		lieu.y = 20;
		switch(select->type){
		case 0:
			sprintf(text,"%s","TERRAIN : HERBE");
			break;
		case 1:
			sprintf(text,"%s","TERRAIN : MONTAGNE");
			break;
		case 2:
			sprintf(text,"%s","TERRAIN : CHEMIN");
			break;
		case 3:
			sprintf(text,"%s","TERRAIN : EAU");
			break;
		case 4:
			sprintf(text,"%s","TERRAIN : DEBUT");
			break;
		case 5:	
			sprintf(text,"%s","TERRAIN : FIN");
			break;
		default:
			break;
		}
		ecrire_texte(police , lieu , screen , text , vert);
		if (select->type == 0)
		{
			lieu.x = 823;
			lieu.y = 50;
			sprintf(text , "%s" , "TOUR : ");
			if (select->tr.active == 0)
			{
				strcat(text,"NON ACTIVE");
			}
			else
			{
				strcat(text,"ACTIVE");
			}
			ecrire_texte(police , lieu , screen , text , vert);
			if (select->tr.active == 1)
			{
				char type[100];
				switch (select->tr.type){
				case P:
					sprintf(type , "P");
					break;
				case V:
					sprintf(type , "V");
					break;
				case H:
					sprintf(type , "H");
					break;
				case HV:
					sprintf(type , "HV");
					break;
				case HP:
					sprintf(type , "HP");
					break;
				case B:
					sprintf(type , "B");
					break;
				}

				position.x = 823;
				position.y = 718;
				SDL_SetColorKey(tab_image_info[3], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			   	SDL_BlitSurface(tab_image_info[3], NULL, screen, &position);
				lieu.x = 880;
				lieu.y = 723;
				sprintf(text , "VENTE");
				ecrire_texte(police , lieu , screen , text , vert);
				lieu.x = 880;
				lieu.y = 743;
				sprintf(text , "%s%d","GAIN : ",calcul_vente(select->tr.level));
				ecrire_texte(police , lieu , screen , text , vert);				


				lieu.x = 823;
				lieu.y = 70;
				sprintf(text , "NIVEAU : %s%d",type,select->tr.level);
				ecrire_texte(police , lieu , screen , text , vert);

				sprintf(text , "%s%d" , "DEGATS : ",select->tr.dmg);
				lieu.y = 90;
				ecrire_texte(police , lieu , screen , text , rouge);

				lieu.y = 110;
				sprintf(text , "%s%d" , "CHARGEMENT : ",select->tr.timer);
				ecrire_texte(police , lieu , screen , text , bleu);

				lieu.y = 130;
				sprintf(text , "%s%d" , "PORTEE : ",select->tr.range);
				ecrire_texte(police , lieu , screen , text , vert);

				lieu.x = 823;
				lieu.y = 562;
				sprintf(text , "AMELIORATIONS");
				ecrire_texte(police , lieu , screen , text , vert);

			if (select->tr.level !=3)
			{
				position.x = 823;
				position.y = 650;
				SDL_SetColorKey(tab_image_info[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			   	SDL_BlitSurface(tab_image_info[1], NULL, screen, &position);
				lieu.x = 880;
				lieu.y = 655;
				sprintf(text , "VITESSE");
				ecrire_texte(police , lieu , screen , text , bleu);
				lieu.x = 880;
				lieu.y = 675;
				sprintf(text , "%s%d","Prix : ",select->tr.amelio);
				ecrire_texte(police , lieu , screen , text , vert);


				position.x = 823;
				position.y = 582;
				SDL_SetColorKey(tab_image_info[0], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			   	SDL_BlitSurface(tab_image_info[0], NULL, screen, &position);
				lieu.x = 880;
				lieu.y = 587;
				sprintf(text , "PUISSANCE");
				ecrire_texte(police , lieu , screen , text , rouge);
				lieu.x = 880;
				lieu.y = 607;
				sprintf(text , "%s%d","Prix : ",select->tr.amelio);
				ecrire_texte(police , lieu , screen , text , vert);
			}
			else
			{
				lieu.x = 823;
				lieu.y = 602;
				sprintf(text , "TOUR NIVEAU MAX");
				ecrire_texte(police , lieu , screen , text , vert);
			}
				
			
				
			}
			else
			{
				if (select->tr.level == -1)
				{
					position.x = 823;
					position.y = 582;
					SDL_SetColorKey(tab_image_info[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
				   	SDL_BlitSurface(tab_image_info[2], NULL, screen, &position);

					lieu.x = 880;
					lieu.y = 587;
					sprintf(text , "ACHAT");
					ecrire_texte(police , lieu , screen , text , vert);
					lieu.x = 880;
					lieu.y = 607;
					sprintf(text , "%s%d","Prix : ",select->tr.amelio);
					ecrire_texte(police , lieu , screen , text , vert);
				}
			}
				
		}
		
	}
	else
	{
		lieu.x = 823;
		lieu.y = 20;
		sprintf(text , "AUCUNE SELECTION");
		ecrire_texte(police , lieu , screen , text , vert);
	}

		
	
}

void affichage_fond_info_case(SDL_Surface *fond , SDL_Surface *screen)
{
	SDL_Rect position;
	position.x = 816;
	position.y = 0;
	SDL_BlitSurface(fond , NULL , screen , &position);
}

int check_pv_joueur(int pv)
{
	if (pv <= 0)
		return 0;
	return 1;
}

void dmg_joueur(int *vie , enn *ennemi , coor lieu)
{
	if (ennemi->c.x >= lieu.x && ennemi->c.y >=lieu.y && ennemi->c.x < lieu.x + 48 && ennemi->c.y < lieu.y +48)
	{
		*vie -= ennemi->dmg;
		supp_ennemi(ennemi);
	}
}

void check_pos_ennemis(enn *ennemis , int *vie , cm **carte)
{
	coor lieu = {(emplacementFin(carte)%17)*48 , (emplacementFin(carte)/17)*48};
	for (int i = 0 ; i <600 ; i++)
	{
		dmg_joueur(vie , &ennemis[i] , lieu);
	}
}

int calcul_longueur_chemin(coor *chemin)
{
	int i = 0;
	while (chemin[i].x != -1 || chemin[i].y != -1)
	{
		i++;
	}
	return i;
}

void creation_vague(vague *vag)
{
	for (int i = 0 ; i < 10 ; i ++)
	{
		vag[i].lvl = i + 1;
		vag[i].nb_soldat = 1;//nb_soldat_vague(vag[i].lvl);
		vag[i].nb_tank = 1;//nb_tank_vague(vag[i].lvl);
		vag[i].temps_spawn = 35 - 1.5 * vag[i].lvl;
		vag[i].timer_spawn = 0;
		vag[i].temps_avant_deb = 200;
	}
}

void gain_auto_devise(int *devise , int *timer , vague *vag , int niveau_vag)
{
	if (vag[niveau_vag].temps_avant_deb == 0)
	{
		if (*timer <= 0)
		{
			*devise += 10;
			*timer = 10;
		}
		else
		{
			*timer -= 1;
		}
	}
}

int gain_devise_soldat(int lvl)
{
	if (lvl <= 0)
		return 0;
	if (lvl == 1)
		return 25;
	return gain_devise_soldat(lvl -1) + (gain_devise_soldat(lvl-1)/3);
}

int gain_devise_tank(int lvl)
{
	if (lvl <= 0)
		return 0;
	if (lvl == 1)
		return 50;
	return gain_devise_soldat(lvl -1) + (gain_devise_soldat(lvl-1)/3);
}

int prix_amelio(int lvl)
{
	if (lvl <= 0)
		return 550;
	return 550 + prix_amelio(lvl - 1) + prix_amelio(lvl - 1)/8;
}

int nb_tank_restant(enn *ennemis , vague *vag , int num_vague)
{
	int nombre_tank = 0;
	for (int i =0; i < 600; i++)
	{
		if (ennemis[i].active == 1 && ennemis[i].type == TANK)
			nombre_tank++;
	}
	nombre_tank += vag[num_vague].nb_tank;
	return nombre_tank;
}

int nb_soldat_restant(enn *ennemis , vague *vag , int num_vague)
{
	int nombre_soldat = 0;
	for (int i =0; i < 600; i++)
	{
		if (ennemis[i].active == 1 && ennemis[i].type == SOLDAT)
			nombre_soldat++;
	}
	nombre_soldat += vag[num_vague].nb_soldat;
	return nombre_soldat;
}

void acheter_amelio_V(cm *select , int *devise)
{
	if (*devise >= select->tr.amelio)
	{
		*devise -= select->tr.amelio;
		spawn_tour_lvl_3(&select->tr ,V);
		spawn_tour_lvl_2(&select->tr ,V);
		spawn_tour_lvl_1(&select->tr ,V);
	}
}

void acheter_amelio_P(cm *select , int *devise)
{
	if (*devise >= select->tr.amelio)
	{
		*devise -= select->tr.amelio;
		spawn_tour_lvl_3(&select->tr ,P);
		spawn_tour_lvl_2(&select->tr ,P);
		spawn_tour_lvl_1(&select->tr ,P);
	}
}

void acheter_tour(cm *select , int *devise)
{
	if (*devise >= select->tr.amelio)
	{
		*devise -= select->tr.amelio;
		spawn_tour_lvl_0(&select->tr);
	}
}

void clic_gauche(coor cursor , cm *select , int *devise)
{
	if (select->type == 0)
	{
		if (select->tr.active == 0)
		{
			if (cursor.x >= 823 && cursor.y >= 582 && cursor.x <= 871 && cursor.y <= 630)
			{
				acheter_tour(select , devise);
			}
		}
		else
		{
			if (cursor.x >= 823 && cursor.y >= 718 && cursor.x <= 871 && cursor.y <= 766)
			{
				supp_tour(&select->tr , devise);
			}
			else
			{	
				if(select->tr.level < 3)
				{
					if (cursor.x >= 823 && cursor.y >= 582 && cursor.x <= 871 && cursor.y <= 630)
					{
						acheter_amelio_P(select , devise);
					}
					if (cursor.x >= 823 && cursor.y >= 650 && cursor.x <= 871 && cursor.y <= 698)
					{
						acheter_amelio_V(select , devise);
					}
				}
			}
		}
			
	} 
}

void defile_vague(vague *vag , enn *ennemis , int *niveau_vague , coor *chemin)
{
	if (*niveau_vague == -1)
		return;
	int random = 0;
	time_t t;
	srand((unsigned) time(&t));
	if (vag[*niveau_vague].temps_avant_deb > 0)
	{
		vag[*niveau_vague].temps_avant_deb--;
	}
	else
	{
		if (vag[*niveau_vague].timer_spawn > 0)
		{
			vag[*niveau_vague].timer_spawn--;
		}
		else
		{
			random = 1+(rand() % 4);
			if(random == 4)
			{
				if (vag[*niveau_vague].nb_tank > 0)
				{
					spawn_tank(ennemis , chemin[0] , vag[*niveau_vague].lvl);
					vag[*niveau_vague].nb_tank--;
				}
				else
				{
					if (vag[*niveau_vague].nb_soldat > 0)
					{
						spawn_soldat(ennemis , chemin[0] , vag[*niveau_vague].lvl);
						vag[*niveau_vague].nb_soldat--;
					}
				}
			}
			else
			{
				if (vag[*niveau_vague].nb_soldat > 0)
				{
					spawn_soldat(ennemis , chemin[0] , vag[*niveau_vague].lvl);
					vag[*niveau_vague].nb_soldat--;
				}
				else
				{
					if(vag[*niveau_vague].nb_tank > 0)
					{
						spawn_tank(ennemis , chemin[0] , vag[*niveau_vague].lvl);
						vag[*niveau_vague].nb_tank--;
					}
				}
			}
			vag[*niveau_vague].timer_spawn = vag[*niveau_vague].temps_spawn;
		}	
	}
	if (vag[*niveau_vague].nb_soldat <= 0 && vag[*niveau_vague].nb_tank <= 0)
	{
		if (nb_soldat_restant(ennemis , vag ,*niveau_vague) == 0 && nb_tank_restant(ennemis , vag ,*niveau_vague) == 0)
		{
			if (*niveau_vague != 9)
			{

					(*niveau_vague)++;
			}
			else
			{
					*niveau_vague = -1;
			}
		}
	}
}

void ecrire_pause(TTF_Font *police , SDL_Surface *screen ,SDL_Color color)
{
	coor lieu = {408 - 517/2 , 408 - 131/2};
	ecrire_texte(police , lieu , screen ,"pause", color);
}

int nb_tank_vague(int lvl)
{
	return 5 * lvl;
}

int nb_soldat_vague(int lvl)
{
	return 15 * lvl;
}

int calcul_vente(int lvl)
{
	if (lvl == 0)
		return 500/2;
	return calcul_vente(lvl - 1 ) + prix_amelio(lvl - 1)/2;
}

void ecrire_victoire(TTF_Font *police , SDL_Surface *screen ,SDL_Color color)
{
	coor lieu = {39 , 342};
	ecrire_texte(police , lieu , screen ,"victoire", color);
}

int check_victoire(int pv , vague *vag , enn *ennemis)
{
	return (nb_tank_restant(ennemis , vag , 9) == 0 && nb_soldat_restant(ennemis , vag , 9) == 0 && check_pv_joueur(pv) == 1);
}

int check_defaite(int pv)
{
	return !(check_pv_joueur(pv));
}

void ecrire_defaite(TTF_Font *police , SDL_Surface *screen ,SDL_Color color)
{
	coor lieu = {65 , 342};
	ecrire_texte(police , lieu , screen ,"defaite", color);
}

void tour_danse(cm **carte ,int *timer)
{
	if (*timer <= 0)
	{
		for (int i = 1; i < 16 ; i++)
		{
			for (int j = 1 ; j < 16 ; j++)
			{
				carte[i][j].tr.anim++;
				if (carte[i][j].tr.anim > 35)
					carte[i][j].tr.anim = 0;
			}
		}
		*timer = 10;
	}
	else
	{
		(*timer)--;
	}
}
		
	
