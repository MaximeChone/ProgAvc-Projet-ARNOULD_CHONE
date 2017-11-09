enum case_type {HERBE , MONTAGNE , CHEMIN , EAU , DEBUT , FIN};

typedef enum case_type case_type;

struct coord
{
	int x;
	int y;
};

typedef struct coord coor;

struct tower
{
	unsigned int NiveauTour; //Niveau de la tour
	int dmg; //Dégat infligé par la tour
	coor c; //coordonnées de la case
	int active; //Si la tour existe ou non
};

typedef struct tower tower;

struct case_map
{
	coor c;					//coordonnées de la case
	case_type type;       //type du sol
	int occupe;           //si la case est occupé
  	tower tr;             //la tour sur la case
};


typedef struct case_map cm;


enum ennemi_type {SOLDAT , TANK};

typedef enum ennemi_type ennemi_type;

struct ennemi
{
	coor c;	//coordonnées de l'ennemie
	int pv;	//point de vie de l'ennemie
	int armure;// armure de l'ennemie
	int active;//si l'ennemie existe ou non
	ennemi_type type; //type d'ennemie
};

typedef struct ennemi enn;


