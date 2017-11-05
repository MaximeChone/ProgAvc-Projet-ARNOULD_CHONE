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
