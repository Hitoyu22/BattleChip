#include "./../../include/sdl/music.h"


Mix_Music *currentMusic = NULL;

int init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Erreur: SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_Init(MIX_INIT_MP3) == 0) {
        fprintf(stderr, "Erreur: Impossible d'initialiser SDL_mixer: %s\n", Mix_GetError());
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
    }

    return 0;
}

void free_music() {
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }
}

void play_audio(const char *filename) {
    if (Mix_PlayingMusic()) {
        return; 
    }

    free_music();  

    currentMusic = Mix_LoadMUS(filename);
    if (!currentMusic) {
        fprintf(stderr, "Erreur: Impossible de charger la musique: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(currentMusic, 1) == -1) {  
        fprintf(stderr, "Erreur: Impossible de jouer la musique: %s\n", Mix_GetError());
        free_music();
    }
}

void playSong(char *sound) {
    if (Mix_PlayingMusic()) {
        Mix_Chunk *newSound = Mix_LoadWAV(sound);
        if (newSound == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger le son : %s\n", Mix_GetError());
            return;
        }

        if (Mix_PlayChannel(1, newSound, 0) == -1) {
            fprintf(stderr, "Erreur: Impossible de jouer le son : %s\n", Mix_GetError());
        }
        Mix_FreeChunk(newSound);
    } else {
        play_audio(sound);
    }
}

void check_and_free_music() {
    if (!Mix_PlayingMusic() && currentMusic) {
        free_music();
    }
}