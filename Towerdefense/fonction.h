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

