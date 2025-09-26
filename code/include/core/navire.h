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

char cpBoat(Boat * boat1, Boat * boat2);

void placer_navire(Boat *navire, int x, int y, Orientation orientation);

Boat * initBoat(int x, int y, Orientation orientation, int taille,char * nom);

void freeBoat(Boat * boat);

char isAlive(Boat * boat);

void initialiser_flotte(Boat flotte[], int *nb_navires);

#endif
