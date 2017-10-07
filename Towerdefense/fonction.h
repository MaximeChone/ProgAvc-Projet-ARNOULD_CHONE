#include <stdio.h>

enum case_type {HERBE , MONTAGNE , CHEMIN , EAU , DEBUT , FIN};

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

void lectureNiveau(cm **carte);
void afficheMap(SDL_Surface **TabImageCase,cm **carte,SDL_Surface *screen);
