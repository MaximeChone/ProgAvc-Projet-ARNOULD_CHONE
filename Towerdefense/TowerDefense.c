#include "fonction.h"
#include <SDL_ttf.h>

int main(int argc,  char *argv[])
{
	int i;
	int gameover = 0;
	SDL_Surface *screen , *temp , *temp2 , *temp3,*temp4,*temp5 , *temp6 , *temp7 , *temp8 , *temp9 , *cursor_image , *fond_image;
	SDL_Surface *TabImageCase[6];
	SDL_Surface *tab_image_ennemis[2];
	SDL_Surface *tab_image_tir[1];
	SDL_Surface *tab_image_tour[10];

	int d = 50;
	char key[SDLK_LAST] = {0};

	coor chemin[127];
	coor cursor = {0,0};

	ini_chemin(chemin);

	enn ennemis[600];
	init_ennemis(ennemis);

	sh tirs[500];
	init_tirs(tirs);

	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption("Tower Defense", "Tower Defense");


	TTF_Font *police = TTF_OpenFont("police.ttf" , 20);
	
	screen = SDL_SetVideoMode(1000 ,816 , 0, 0);
	cursor_image = SDL_DisplayFormat(SDL_LoadBMP("cursor.bmp"));
	fond_image = SDL_DisplayFormat(SDL_LoadBMP("fond_info.bmp"));
	temp = SDL_LoadBMP("herbe.bmp");
	TabImageCase[0]=SDL_DisplayFormat(temp);
	temp2 = SDL_LoadBMP("montagne.bmp");
	TabImageCase[1]=SDL_DisplayFormat(temp2);
	temp3 = SDL_LoadBMP("chemin.bmp");
	TabImageCase[2]=SDL_DisplayFormat(temp3);
	temp4 = SDL_LoadBMP("eau.bmp");
	TabImageCase[3]=SDL_DisplayFormat(temp4);
	temp5 = SDL_LoadBMP("spawn1.bmp");
	TabImageCase[4]=SDL_DisplayFormat(temp5);
	temp6 = SDL_LoadBMP("spawn2.bmp");
	TabImageCase[5]=SDL_DisplayFormat(temp6);
	temp7 = SDL_LoadBMP("spriteSoldat1.bmp");
	tab_image_ennemis[0] = SDL_DisplayFormat(temp7);
	tab_image_ennemis[1] = SDL_DisplayFormat(SDL_LoadBMP("tank.bmp"));
	temp8 = SDL_LoadBMP("bullet.bmp");
	tab_image_tir[0] = SDL_DisplayFormat(temp8);
	temp9 = SDL_LoadBMP("TowerB.bmp");
	tab_image_tour[0] = SDL_DisplayFormat(temp9);
	tab_image_tour[1] = SDL_DisplayFormat(SDL_LoadBMP("TowerP1.bmp"));
	tab_image_tour[2] = SDL_DisplayFormat(SDL_LoadBMP("TowerV1.bmp"));
	tab_image_tour[3] = SDL_DisplayFormat(SDL_LoadBMP("TowerP2.bmp"));
	tab_image_tour[4] = SDL_DisplayFormat(SDL_LoadBMP("TowerH.bmp"));
	tab_image_tour[5] = SDL_DisplayFormat(SDL_LoadBMP("TowerV2.bmp"));
	tab_image_tour[6] = SDL_DisplayFormat(SDL_LoadBMP("TowerP3.bmp"));
	tab_image_tour[7] = SDL_DisplayFormat(SDL_LoadBMP("TowerHP.bmp"));
	tab_image_tour[8] = SDL_DisplayFormat(SDL_LoadBMP("TowerHV.bmp"));
	tab_image_tour[9] = SDL_DisplayFormat(SDL_LoadBMP("TowerV3.bmp"));
	
	cm **carte = malloc(sizeof(struct case_map*) *17);
	cm *select = NULL;
	for (i=0 ; i <17; i++)
	{
		carte[i] = malloc(sizeof(struct case_map) * 17);
	}

	lectureNiveau(carte);

	int possible_chemin = verifChemin(carte);
	defchemin(carte , emplacementDebut(carte)/17 , emplacementDebut(carte)%17 ,'e',chemin ,0);
	spawn_soldat(ennemis , chemin[0] , 1);
	spawn_tour_lvl_1(&carte[12][6].tr);
	spawn_tour_lvl_1(&carte[13][6].tr);
	spawn_tour_lvl_2(&carte[12][6].tr,V);
	spawn_tour_lvl_3(&carte[12][6].tr,V);
	spawn_tour_lvl_4(&carte[12][6].tr,V);
	spawn_tour_lvl_2(&carte[13][6].tr,P);
	spawn_tour_lvl_3(&carte[13][6].tr,P);
	spawn_tour_lvl_4(&carte[13][6].tr,P);
	spawn_tour_lvl_1(&carte[10][6].tr);
	spawn_tour_lvl_2(&carte[10][6].tr,V);
	spawn_tour_lvl_1(&carte[9][6].tr);
	spawn_tour_lvl_2(&carte[9][6].tr,P);
	spawn_tour_lvl_1(&carte[11][6].tr);
	spawn_tour_lvl_2(&carte[11][6].tr,V);
	spawn_tour_lvl_3(&carte[11][6].tr,P);
	spawn_tour_lvl_1(&carte[8][6].tr);
	spawn_tour_lvl_2(&carte[8][6].tr,P);
	spawn_tour_lvl_3(&carte[8][6].tr,P);
	spawn_tour_lvl_4(&carte[8][6].tr,V);

	SDL_Color color = {255,255,255};
	int pv;
	pv = 15;
	while (!(gameover) && possible_chemin && check_pv_joueur(pv))
		{
			evenement_clavier(key,&gameover,&cursor , &select , carte);
			if (select != NULL)
				printf("x = %f , y = %f\n",select->c.x , select->c.y);
			evenement_verifClavier(key,&d,ennemis ,chemin[0]);

			affichage_fond_info_case(fond_image , screen);
			afficheMap(TabImageCase ,carte , screen);
			affichage_ennemi(ennemis , tab_image_ennemis , screen);
			affichage_tir(tab_image_tir , tirs , screen);
			affichage_tour(tab_image_tour , carte , screen);

	 		barre_vie_ennemis(ennemis , screen);

			//affichage_cursor(cursor_image ,cursor , screen);
			ecrire_info_case_select(select , police  , screen ,color );

			check_range(carte , ennemis ,tirs);

			timer_tours(carte);

			ennemis_moove(ennemis , chemin);
			tirs_moove(tirs , ennemis);

			check_vie(ennemis);
			check_pos_ennemis(ennemis ,&pv ,carte);

			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(d);
		}
	printf("test : %d\n",calc_pv_tank(10));
	printf("test : %d\n",calc_pv_soldat(10));
	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);
	for (i=0 ; i < 6; i++)
		SDL_FreeSurface(TabImageCase[i]);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp2);
	SDL_FreeSurface(temp3);
	SDL_FreeSurface(temp4);
	SDL_FreeSurface(temp5);
	SDL_FreeSurface(temp6);
	SDL_FreeSurface(temp7);
	SDL_FreeSurface(temp8);
	SDL_FreeSurface(temp9);
	SDL_FreeSurface(fond_image);
	SDL_FreeSurface(cursor_image);
	TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
	
