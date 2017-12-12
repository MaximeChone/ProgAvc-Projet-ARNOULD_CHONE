#include "fonction.h"
#include <SDL_ttf.h>

int main(int argc,  char *argv[])
{
	int i;

	SDL_Surface *screen , *temp , *temp2 , *temp3,*temp4,*temp5 , *temp6 , *temp7 , *temp8 , *temp9 ,  *fond_image;
	SDL_Surface *TabImageCase[6];
	SDL_Surface *tab_image_ennemis[2];
	SDL_Surface *tab_image_tir[1];
	SDL_Surface *tab_image_tour[10];
	SDL_Surface *tab_image_info[4];
	//SDL_Surface *cursor_image;

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
	TTF_Font *police_big = TTF_OpenFont("police.ttf" , 200);
	
	screen = SDL_SetVideoMode(1000 ,816 , 0, 0);

	//cursor_image = SDL_DisplayFormat(SDL_LoadBMP("cursor.bmp"));
//517
//131
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
	tab_image_tour[7] = SDL_DisplayFormat(SDL_LoadBMP("Tower1HP.bmp"));
	tab_image_tour[8] = SDL_DisplayFormat(SDL_LoadBMP("TowerHV.bmp"));
	tab_image_tour[9] = SDL_DisplayFormat(SDL_LoadBMP("TowerV3.bmp"));

	tab_image_info[0] = SDL_DisplayFormat(SDL_LoadBMP("up_p.bmp"));
	tab_image_info[1] = SDL_DisplayFormat(SDL_LoadBMP("up_v.bmp"));
	tab_image_info[2] = SDL_DisplayFormat(SDL_LoadBMP("achat.bmp"));
	tab_image_info[3] = SDL_DisplayFormat(SDL_LoadBMP("vendre.bmp"));
	
	cm **carte = malloc(sizeof(struct case_map*) *17);
	cm *select = NULL;
	for (i=0 ; i <17; i++)
	{
		carte[i] = malloc(sizeof(struct case_map) * 17);
	}

	int lecture = lectureNiveau(carte);
	int possible_chemin = 0;
	if ( lecture == 1)
	{
		possible_chemin = verifChemin(carte);
		if (possible_chemin)
			defchemin(carte , emplacementDebut(carte)/17 , emplacementDebut(carte)%17 ,'e',chemin ,0);
	}
	SDL_Color vert = {0,255,0};
	SDL_Color rouge = {255,0,0};
	SDL_Color bleu = {0,0,255};
	SDL_Color blanc = {255,255,255};

	int pv = 15;
	int devise = 1500;
	int timer_devise = 10;
	int niveau_vague = 0;
	int pause = 0;
	int gameover = 0;
	int exit = 0;
	int timer_danse = 0;

	vague vag[10];
	creation_vague(vag);

	while (!(exit) && possible_chemin == 1)
		{

			affichage_fond_info_case(fond_image , screen);
			afficheMap(TabImageCase ,carte , screen);
			affichage_ennemi(ennemis , tab_image_ennemis , screen);
			affichage_tir(tab_image_tir , tirs , screen);
			affichage_tour(tab_image_tour , carte , screen);
	 		barre_vie_ennemis(ennemis , screen);
			ecrire_info_case_select(select , police  , screen ,vert , bleu , rouge,devise ,tab_image_info , vag , ennemis ,niveau_vague,pv);


			while (pause == 1 && !(exit))//boucle pause
			{
				ecrire_pause(police_big ,screen ,blanc);
				evenement_clavier(key,&gameover,&cursor , &select , carte , &devise , &pause , &exit);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
			}
			while ((check_defaite(pv) && !(exit)) || gameover == 1)//boucle défaite
			{
				gameover = 1;
				ecrire_defaite(police_big ,screen ,blanc);
				evenement_clavier(key,&gameover,&cursor , &select , carte , &devise , &pause , &exit);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
			}
			while (check_victoire(pv , vag , ennemis) && !(exit))//boucle victoire
			{
				gameover = 1;

				evenement_clavier(key,&gameover,&cursor , &select , carte , &devise , &pause , &exit);
				afficheMap(TabImageCase ,carte , screen);
				tour_danse(carte , &timer_danse);
				affichage_tour(tab_image_tour , carte , screen);
				ecrire_victoire(police_big ,screen ,blanc);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
			}

			evenement_clavier(key,&gameover,&cursor , &select , carte , &devise , &pause , &exit);
			evenement_verifClavier(key,&d);
			defile_vague(vag , ennemis , &niveau_vague , chemin);



			gain_auto_devise(&devise , &timer_devise , vag , niveau_vague);

			//affichage_cursor(cursor_image ,cursor , screen);



			check_range(carte , ennemis ,tirs);
			timer_tours(carte);
			ennemis_moove(ennemis , chemin);
			tirs_moove(tirs , ennemis);
			check_vie(ennemis, &devise);
			check_pos_ennemis(ennemis ,&pv ,carte);

			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(d);
		}

	erreurs(lecture , possible_chemin);
	coor lieu = {0,0};
	ecrire_texte(police_big , lieu , screen , "defaite" , blanc);		
	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);
	for (i=0 ; i < 6; i++)
		SDL_FreeSurface(TabImageCase[i]);
	for (i=0 ; i < 10 ; i++)
		SDL_FreeSurface(tab_image_tour[i]);
	for (i=0 ; i < 2 ; i++)
		SDL_FreeSurface(tab_image_ennemis[i]);
	for (i=0 ; i < 1 ; i++)
		SDL_FreeSurface(tab_image_tir[i]);
	for (i=0 ; i < 3 ; i++)
		SDL_FreeSurface(tab_image_info[i]);

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
	//SDL_FreeSurface(cursor_image);
	TTF_CloseFont(police);
	TTF_CloseFont(police_big);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
	
