#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

extern Mix_Music *currentMusic;

/**
 * Initialisation de l'audio
 */
int init_audio();

/**
 * Lecture d'un son
 * @param sound : le son à jouer
 */
void playSong(char *sound);


#endif