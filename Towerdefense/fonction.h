#include <stdio.h>

enum case_type {HERBE , MONTAGNE , CHEMIN_H , CHEMIN_V , CHEMIN_BG , CHEMIN_BD , CHEMIN_HG , CHEMIN_HD , DEBUT , FIN};

typedef enum case_type case_type;

struct tower
{
};

typedef struct tower tour;

struct case_map
{
	case_type type;       //type du sol
	int occupe;           //si la case est occupé
	tour tour;           //la tour sur la case
};

typedef struct case_map cm;
