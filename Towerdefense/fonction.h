#include "struct.h"
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#define PI 3.14159265358979323846

void lectureNiveau(cm **carte);//prend le fichier niveau , le lit , remplis les types des cases

int verifChemin(cm **carte);//vérifie si le chemin est valide 
int sous_verifchemin_1(cm **carte, int i , int j);//sous fonction de verifChemin
int sous_verifchemin_2(cm **carte, int i , int j);//sous fonction de verifChemin
int sous_verifchemin_3(cm **carte, int i , int j);//sous fonction de verifChemin
int sous_verifchemin_4(cm **carte, int i , int j);//sous fonction de verifChemin
int sous_verifchemin_5(cm **carte, int i , int j);//sous fonction de verifChemin
int sous_verifchemin_6(cm **carte, int i , int j);//sous fonction de verifChemin

int emplacementDebut(cm **carte);//renvoie l'emplacement de la case 'd'
void defchemin(cm **carte , int i , int j , char sens , coor *chemin , int compteurChemin);//entre chaque coordonnées du chemin dans un tableau de coordonnées
int emplacementFin(cm **carte);//renvoie l'emplacement de la case 'f'

void evenement_verifClavier(char* key,int *d , enn *ennemis , coor lieu);//evenement clavier
void evenement_clavier(char* keys,int *gameover,coor *cursor , cm **selec, cm **carte);//evenement clavier

void ini_chemin(coor *chemin);//initialise le tableau de coordonnées
void init_ennemis(enn *ennemis);//initialise le tableau d'ennemis
void init_tirs(sh *tirs);//initialise le tableau de tirs

void ennemi_moove(enn *ennemi , coor *chemin);//fait bouger un ennemi
void tir_moove(sh *tir , enn *ennemis);//fait bouger un tir
void ennemis_moove(enn *ennemi , coor *chemin);//fait bouger tous les ennemis
void tirs_moove(sh *tirs , enn *ennemis);//fait bouger tous les tirs

void anim_ennemi_haut(enn *ennemi);//change l'animation de l'ennemi vers le haut
void anim_ennemi_bas(enn *ennemi);//change l'animation de l'ennemi vers le bas
void anim_ennemi_droite(enn *ennemi);//change l'animation de l'ennemi vers la droite
void anim_ennemi_gauche(enn *ennemi);//change l'animation de l'ennemi vers la gauche
void anim_tour(tower *tour, float angle);//change l'animation de la tour selon l'angle
void anim_tir(sh *tir);//change l'animation du tir selon l'angle

void spawn_soldat(enn *ennemis , coor lieu , int lvl);//fait apparaite un soldat au lieu indiqué
void spawn_tour_lvl_1(tower *tour);//fait apparaitre une tour de niveau 1
void spawn_tir(sh *tirs , int cible , tower *tour);//fait apparaitre un tir sur la tour indiqué

void affichage_fond_info_case(SDL_Surface *fond , SDL_Surface *screen);
void affichage_ennemi(enn *ennemis , SDL_Surface **tab_image_ennemis , SDL_Surface *screen);//affiche les ennemis
void affichage_tour(SDL_Surface **tab_image_tour , cm **carte , SDL_Surface *screen);//affiche les tours
void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen);//affiche la carte
void affichage_tir(SDL_Surface **tab_image_tir , sh *tir , SDL_Surface *screen);//affiche les tirs
void affichage_cursor(SDL_Surface *cursor_image , coor cursor, SDL_Surface *screen);//affiche le curseur

void supp_tour_lvl_1(tower *tour);//supprime la tour de niveau 1
void supp_tir(sh *tir);//supprime le tir
void supp_ennemi(enn *enemi);//supprime l'ennemi

void damage(int dmg , enn *ennemi);//inflige les dégats à l'ennmi

void check_vie(enn *ennemis);//regarde les points de vie des ennemis et les supprimes si leurs points de vie sont inférieur à 1
void check_range(cm **carte , enn *ennemis, sh *tirs);//regarde la portée des tours et tirs si son timer est bon et qu'un ennemi est dans sa portée
int check_tir_dmg_suffisant(enn *ennemis , int cible , sh *tirs);//regarde si il y a assez de tirs en l'air pour tuer ennemis[cible]

void timer_tours(cm **carte);//incrémente de 1 le timer des tours

float calcul_angle_tour(float x1 , float y1 , float x2,float y2 , int sprite_taille_1 , int sprite_taille_2);//calcul de l'angle entre le centre du sprite_taille_1 d'une tour (x1/y1) et du centre du sprite_taille_2 d'un ennemi(x2/y2) 
float calcul_angle_tir(float x1 , float y1 , float x2,float y2 , int sprite_taille_1 , int sprite_taille_2);//calcul de l'angle entre un tir(x1/y1) et du centre du sprite_taille_2 d'un ennemi(x2/y2)

void barre_vie_ennemi(enn ennemi , SDL_Surface *screen);//affiche la barre de vie d'un ennemi
void barre_vie_ennemis(enn *ennemis , SDL_Surface *screen);//affiche les barres de vie de tous les ennemis

void selection(cm **carte , int x , int y , cm **select);//selectionne une case
void deselection(cm **select);//déselectionne la case

void ecrire_texte(TTF_Font *police , coor lieu , SDL_Surface *screen , char *texte ,SDL_Color color );
void ecrire_info_case_select(cm *select , TTF_Font *police  , SDL_Surface *screen ,SDL_Color color );

int calc_pv_soldat(int lvl);

int check_pv_joueur(int pv);
void dmg_joueur(int *vie , enn *ennemi , coor lieu);
void check_pos_ennemis(enn *ennemis , int *vie , cm **carte);
int calcul_longueur_chemin(coor *chemin);
void creation_vague(vague *vag , coor *chemin);
