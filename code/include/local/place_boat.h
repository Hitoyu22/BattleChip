#ifndef PLACE_BOAT_H
#define PLACE_BOAT_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../../include/sdl/sdl_utils.h"

typedef struct {
    int posX;
    int posY;
    char orientation;
} BoatPosition;



int place_boats_visual(int rows, int columns, char **table, SDL_Renderer *renderer);


#endif