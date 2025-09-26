#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "./../include/sdl/sdl_utils.h"
#include "./../include/core/menu.h"

#define WIDTH_SIZE = 1000;
#define HEIGHT_SIZE = 1000;

int main(int argc, char * argv[]) {
    char * throw;
    sscanf(argv[argc-1], "%ms", &throw);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    

    if (!initSDL(&window, &renderer, "BattleChip", 1000, 1000)) {
        return 1; 
    }

    handle_menu(renderer, 1000, 1000);

    closeSDL(window, renderer);

    return 0;
}