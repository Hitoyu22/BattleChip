#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int player_id;
    int screen; // 0 pour soi, 1 pour ennemi 
    int character;
    int choice_position; // 0 pour manuel, 1 pour auto
} Player;


void start_solo_mode(SDL_Renderer *renderer);

#endif
