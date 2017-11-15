#include "struct.h"
void lectureNiveau(cm **carte);
void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen);
int verifChemin(cm **carte);
int sous_verifchemin_1(cm **carte, int i , int j);
int sous_verifchemin_2(cm **carte, int i , int j);
int sous_verifchemin_3(cm **carte, int i , int j);
int sous_verifchemin_4(cm **carte, int i , int j);
int sous_verifchemin_5(cm **carte, int i , int j);
int sous_verifchemin_6(cm **carte, int i , int j);
void ini_chemin(coor *chemin);
int emplacementDebut(cm **carte);
void defchemin(cm **carte , int i , int j , char sens , coor *chemin , int compteurChemin);
void evenement_verifClavier(char* key,int *d);
void evenement_clavier(char* keys,int *gameover);
void init_ennemis(enn *ennemis);
void ennemi_moove(enn *ennemi , coor *chemin);
void ennemis_moove(enn *ennemi , coor *chemin);
void affichage_ennemi(enn *ennemis , SDL_Surface **tab_image_ennemis , SDL_Surface *screen);
void anim_ennemi_haut(enn *ennemi);
void anim_ennemi_bas(enn *ennemi);
void anim_ennemi_droite(enn *ennemi);
void anim_ennemi_gauche(enn *ennemi);
void spawn_soldat(enn *ennemis , coor lieu);
void spawn_tour(tower *tour);
void affichage_tour(SDL_Surface **tab_image_tour , cm **carte , SDL_Surface *screen);

