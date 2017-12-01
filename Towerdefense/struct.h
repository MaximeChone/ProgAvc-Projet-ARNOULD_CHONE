enum case_type {HERBE , MONTAGNE , CHEMIN , EAU , DEBUT , FIN};
typedef enum case_type case_type;
enum tower_type {B ,P , V , H};
typedef enum tower_type t_type;
enum ennemi_type {SOLDAT , TANK};
typedef enum ennemi_type ennemi_type;


struct coord
{
	float x;
	float y;
};

typedef struct coord coor;

struct tower
{
	t_type type;
	int level; //Niveau de la tour
	int dmg; //Dégat infligé par la tour
	coor c; //coordonnées de la case
	int active; //Si la tour existe ou non
	int taille_sprite;
	int anim;
	int range;
	int cooldown;
	int timer;
};

typedef struct tower tower;

struct case_map
{
	coor c;					//coordonnées de la case
	case_type type;       //type du sol
	int occupe;           //si la case est occupé
  	tower tr;             //la tour sur la case
	int taille_sprite;
	int anim;

};


typedef struct case_map cm;

struct ennemi
{
	coor c;	//coordonnées de l'ennemi
	int pv;	//point de vie de l'ennemi
	int pv_max;
	int pa;// armure de l'ennemi
	int active;//si l'ennemie existe ou non
	ennemi_type type; //type d'ennemi
	int chem; //positon sur le chemin
	int v; //vitesse de l'ennemi
	int anim;//animation actuelle
	int taille_sprite;
	int lvl;
	int dmg;
};

typedef struct ennemi enn;

struct shoot
{
	coor c; //coordonnées du tir
	int cible; //cible du tir
	int v;// vitesse du tir
	int dmg; //dégats du tir
	int active; //si le tir existe ou non
	int taille_sprite;
	int anim;
};

typedef struct shoot sh;

struct vague
{
	int lvl;
	int nb_soldat;
	int nb_tank;
	int temps_spawn;
	int timer_spawn;
	int temps_avant_deb;
};

typedef struct vague vague;	
