#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../../include/sdl/sdl_utils.h"
#include "./../../include/core/menu.h"
#include "./../../include/local/game.h"


#define TILE_SIZE 64

void start_local_mode(){

    printf("Local Mode\n");

}

void start_multiplayer_mode(){

    printf("Multiplayer Mode\n");

}

void render_menu(SDL_Renderer *renderer, int selected_option, SDL_Texture *background, TTF_Font *font, int width, int height) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};

    SDL_RenderClear(renderer);

    render_texture(renderer, background, 0, 0, width, height); 

    int title_size = height / 8; 
    TTF_Font *title_font = TTF_OpenFont("./assets/fonts/font.ttf", title_size);
    if (!title_font) title_font = font;

    const char *title_text = "BattleChip";
    int title_w, title_h;
    TTF_SizeText(title_font, title_text, &title_w, &title_h);
    int title_x = (width - title_w) / 2;
    int title_y = height / 10; 
    render_text(renderer, title_text, title_x, title_y, title_font, white);

    if (title_font != font) {
        TTF_CloseFont(title_font);
    }

    const char *labels[] = {"Jouer en solo", "Multijoueur local", "Multijoueur", "Quitter"};
    int n_options = 4;

    int font_size = height / 15; 
    TTF_Font *scaled_font = TTF_OpenFont("./assets/fonts/font.ttf", font_size);
    if (!scaled_font) scaled_font = font; 

    int total_height = n_options * font_size + (n_options - 1) * (font_size / 2);
    int start_y = (height - total_height) / 2 + height / 10;

    for (int i = 0; i < n_options; i++) {
        SDL_Color color = (i == selected_option) ? white : black;

        int text_w, text_h;
        TTF_SizeText(scaled_font, labels[i], &text_w, &text_h);
        int x = (width - text_w) / 2;
        int y = start_y + i * (text_h + font_size / 2);

        render_text(renderer, labels[i], x, y, scaled_font, color);
    }

    SDL_RenderPresent(renderer);

    if (scaled_font != font) {
        TTF_CloseFont(scaled_font);
    }
}


void handle_menu(SDL_Renderer *renderer, int width, int height) {
    int running = 1;
    int selected_option = 0;
    SDL_Event event;

    SDL_Texture *background = load_texture(renderer, "./assets/images/fond.jpg");
    if (!background) {
        fprintf(stderr, "Erreur lors du chargement de la texture de fond.\n");
        return;
    }

    TTF_Font *font = load_font("./assets/fonts/font.ttf", 28);
    if (!font) {
        fprintf(stderr, "Impossible de charger la police.\n");
        SDL_DestroyTexture(background);
        return;
    }

    void (*menu_options[])(SDL_Renderer *renderer) = {
        start_solo_mode,       
        start_local_mode,      
        start_multiplayer_mode, 
    };

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_UP) {
                        selected_option = (selected_option - 1 + 4) % 4;
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        selected_option = (selected_option + 1) % 4;
                    } else if (event.key.keysym.sym == SDLK_RETURN) {
                        if (selected_option < 3) {
                            menu_options[selected_option](renderer); 
                        } else {
                            running = 0;
                        }
                    }
                    break;
            }
        }
        render_menu(renderer, selected_option, background, font, width, height);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(background);
    TTF_CloseFont(font);
}