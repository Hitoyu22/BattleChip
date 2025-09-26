#ifndef START_PLAYER_H
#define START_PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SELECT_NONE   -1  // rien de sélectionné
#define SELECT_CELL    1  // une case a été cliquée
#define SELECT_SWITCH  2  // appui sur E pour changer de point de vue
#define SELECT_QUIT    0  // quitter ou appui sur ESC


/**
 * @param player : Numéro du joueur
 * @param character : pointeur sur le personnage choisi
 * @param renderer : Renderer de SDL 
 */
int show_player_choice(int player, int *character, int * choice_position, SDL_Renderer *renderer);

#endif