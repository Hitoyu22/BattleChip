#ifndef NAVIRE_H
#define NAVIRE_H

typedef enum
{
    HORIZONTAL,
    VERTICAL
} Orientation;

typedef enum
{
    WATER,
    SHOT_WATER,
    BOAT,
    SHOT_BOAT,
    KILLED_BOAT
} TILE;

typedef struct
{
    int x;
    int y;
    int taille;
    Orientation orientation;
    int *etat;
    int pv;
    char nom[20];
    int pos;
    int est_coule;
} Boat;

Boat *creer_navire(int taille);

void detruire_navire(Boat *navire);

void placer_navire(Boat *navire, int x, int y, Orientation orientation);

int tirer_sur_navire(Boat *navire, int x_tir, int y_tir);

int navire_est_coule(Boat *navire);

#endif
