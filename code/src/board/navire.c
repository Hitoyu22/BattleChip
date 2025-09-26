#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/core/navire.h"
#include <stdio.h>

char cpBoat(Boat * boat1, Boat * boat2){
    boat1->x = boat2->x;
            printf("test30\n");

    boat1->y = boat2->y;
        printf("test30\n");
    boat1->taille = boat2->taille;
    boat1->orientation = boat2->orientation;
    boat1->etat = malloc(sizeof(int)*boat2->taille);
        printf("test30\n");
    for(int i = 0; i<boat2->taille; i++) (boat1->etat)[i] = (boat2->etat)[i];
    boat1->pv = boat2->x;
    strcpy(boat1->nom,boat2->nom);
    boat1->pos = boat2->pos;
    boat1->est_coule = boat2->est_coule;
    return 1;
}

void placer_navire(Boat *navire, int x, int y, Orientation orientation)
{
    navire->x = x;
    navire->y = y;
    navire->orientation = orientation;
    strcpy(navire->nom,"");
}

Boat * initBoat(int x, int y, Orientation orientation, int taille,char * nom){
    Boat * boat = malloc(sizeof(Boat));
    boat->x = x;
    boat->y = y;
    boat->taille = taille;
    boat->orientation = orientation;
    boat->etat=malloc(sizeof(int)*taille);
    for(int i = 0; i<taille; i++) boat->etat[i] = BOAT;
    if (nom==NULL) nom[0]='\0';
    else strcpy(boat->nom,nom);
    boat->est_coule = 0;
    return boat;   
}

void freeBoat(Boat * boat){
    free(boat->etat);
    free(boat);
}

char isAlive(Boat * boat){
    for(int i = 0; i<boat->taille; i++){
        if (boat->etat[i]==BOAT) return 1 ;
    }
    return 0;
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