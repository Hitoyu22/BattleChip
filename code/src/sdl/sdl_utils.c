#include "./../../include/sdl/sdl_utils.h"
#include <stdio.h>

int initSDL(SDL_Window **window, SDL_Renderer **renderer, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 0; 
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 0; 
    }

    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!*window) {
        fprintf(stderr, "Impossible de créer la fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        fprintf(stderr, "Impossible de créer le rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    return 1; 
}

void closeSDL(SDL_Window *window, SDL_Renderer *renderer) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
}


void render_text(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color) {
    SDL_Surface *text_surface = TTF_RenderUTF8_Solid(font, text, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (text_texture) {
        SDL_Rect text_location = {x, y, text_surface->w, text_surface->h};
        SDL_RenderCopy(renderer, text_texture, NULL, &text_location);
        SDL_DestroyTexture(text_texture);
    }
    SDL_FreeSurface(text_surface);
}

SDL_Texture* load_texture(SDL_Renderer *renderer, const char *file_path) {
    SDL_Surface *surface = IMG_Load(file_path);
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image %s: %s\n", file_path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "Erreur lors de la création de la texture: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int width, int height) {
    SDL_Rect dst_rect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}

TTF_Font* load_font(const char *file_path, int font_size) {
    TTF_Font *font = TTF_OpenFont(file_path, font_size);
    if (!font) {
        fprintf(stderr, "Erreur lors du chargement de la police %s: %s\n", file_path, TTF_GetError());
        return NULL;
    }
    return font;
}

void render_button(SDL_Renderer *renderer, SDL_Rect *button, const char *text, SDL_Color textColor, SDL_Color backgroundColor, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, button);  

    SDL_Surface *textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text, textColor, button->w);
    if (textSurface) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {
            button->x + (button->w - textSurface->w) / 2,  
            button->y + (button->h - textSurface->h) / 2,  
            textSurface->w,
            textSurface->h
        };
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect); 
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    } else {
        fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
    }
}


SDL_Texture* resize_texture(SDL_Renderer* renderer, SDL_Texture* src, int new_w, int new_h) {
    SDL_Texture* target = SDL_CreateTexture(renderer,
                                            SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET,
                                            new_w, new_h);

    SDL_SetRenderTarget(renderer, target);

    SDL_Rect dst = {0, 0, new_w, new_h};
    SDL_RenderCopy(renderer, src, NULL, &dst);

    SDL_SetRenderTarget(renderer, NULL);

    return target;
}


