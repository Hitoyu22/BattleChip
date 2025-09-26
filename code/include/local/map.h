#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "./../../include/local/game.h"

#define SELECT_NONE   -1
#define SELECT_CELL    1 
#define SELECT_SWITCH  2 
#define SELECT_QUIT    0  

typedef struct {
    int posX;
    int posY; 
} SelectedPosition;


int show_map(int rows, int columns, char **table, Player *player, SDL_Renderer *renderer, long timestamp, SelectedPosition *positions);


#endif