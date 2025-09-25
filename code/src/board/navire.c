#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "navire.h"
#include <stdio.h>

void placer_navire(Boat *navire, int x, int y, Orientation orientation)
{
    navire->x = x;
    navire->y = y;
    navire->orientation = orientation;
}

void initialiser_flotte(Boat flotte[], int *nb_navires)
{
    const char *noms[] = {"Porte-avions", "Croiseur", "Destroyer", "Sous-marin", "Torpilleur"};
    const int tailles[] = {5, 4, 3, 3, 2};
    int ligne, col;
    srand(time(NULL));
    char orientation_char;
    Orientation orientation;

    *nb_navires = 5;
    for (int i = 0; i < *nb_navires; i++)
    {
        strcpy(flotte[i].nom, noms[i]);
        flotte[i].taille = tailles[i];
        flotte[i].pv = tailles[i];
        printf("Placer %s (taille %d) :\n", flotte[i].nom, flotte[i].taille);
        printf("Ligne (0-9), Colonne (0-9), Orientation (h/v) : ");
        scanf("%d %d %c", &ligne, &col, &orientation_char);
        orientation = (orientation_char == 'h') ? HORIZONTAL : VERTICAL;
        placer_navire(&flotte[i], col, ligne, orientation);
    }
}