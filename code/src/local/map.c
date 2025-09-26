#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../../include/sdl/sdl_utils.h"
#include "./../../include/local/game.h"
#include "./../../include/local/map.h"
#include "./../../include/core/board.h"

// Inversion rows et columns
int show_map(int columns, int rows, TILE **table, Player *player, SDL_Renderer *renderer, long timestamp, SelectedPosition *positions) {


    SDL_Event event;
    const int width = 1000, height = 1000;
    int grid_size = (width - 100) / columns;
    int start_x = 50, start_y = 50;

    TTF_Font *font = load_font("./assets/fonts/font.ttf", 24);
    SDL_Color white = {255, 255, 255, 255};

    SDL_Texture *img_sananes   = load_texture(renderer, "./assets/images/sananes.png");
    SDL_Texture *img_sananes1  = load_texture(renderer, "./assets/images/sananes1.png");
    SDL_Texture *img_wajnberg  = load_texture(renderer, "./assets/images/wajnberg.png");
    SDL_Texture *img_wajnberg1 = load_texture(renderer, "./assets/images/wajnberg1.png");




    printf("%d\n", player->screen);
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                TTF_CloseFont(font);
                SDL_DestroyTexture(img_sananes);
                SDL_DestroyTexture(img_sananes1);
                SDL_DestroyTexture(img_wajnberg);
                SDL_DestroyTexture(img_wajnberg1);
                return SELECT_QUIT;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_e) {
                    TTF_CloseFont(font);
                    SDL_DestroyTexture(img_sananes);
                    SDL_DestroyTexture(img_sananes1);
                    SDL_DestroyTexture(img_wajnberg);
                    SDL_DestroyTexture(img_wajnberg1);
                    return SELECT_SWITCH;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    TTF_CloseFont(font);
                    SDL_DestroyTexture(img_sananes);
                    SDL_DestroyTexture(img_sananes1);
                    SDL_DestroyTexture(img_wajnberg);
                    SDL_DestroyTexture(img_wajnberg1);
                    return SELECT_QUIT;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;
                int c = (mx - start_x) / grid_size;
                int r = (my - start_y) / grid_size;
                if (r >= 0 && r < rows && c >= 0 && c < columns) {
                    positions->posX = r;
                    positions->posY = c;

                    TTF_CloseFont(font);
                    SDL_DestroyTexture(img_sananes);
                    SDL_DestroyTexture(img_sananes1);
                    SDL_DestroyTexture(img_wajnberg);
                    SDL_DestroyTexture(img_wajnberg1);
                    return SELECT_CELL;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int j = 0; j < columns; j++) {
            char txt[2] = {'A' + j, 0};
            int tw, th;
            TTF_SizeText(font, txt, &tw, &th);
            render_text(renderer, txt, start_x + j*grid_size + (grid_size - tw)/2, start_y - 40, font, white);
        }

        for (int i = 0; i < rows; i++) {
            //if (!table[i]) continue;
            char txt[8];
            snprintf(txt, sizeof(txt), "%d", i+1);
            int tw, th;
            TTF_SizeText(font, txt, &tw, &th);
            render_text(renderer, txt, start_x - 40 + (40 - tw)/2, start_y + i*grid_size + (grid_size - th)/2, font, white);
            for (int j = 0; j < columns; j++) {
                SDL_Rect cell = {start_x + j*grid_size, start_y + i*grid_size, grid_size - 2, grid_size - 2};
                TILE c = table[i][j];
                if (c == BOAT) {
                    if (player->character == 0) {
                        if (player->screen == 0)
                            render_texture(renderer, img_sananes, cell.x, cell.y, cell.w, cell.h);
                        else
                            SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255), SDL_RenderFillRect(renderer, &cell);
                    } else {
                        if (player->screen == 0)
                            render_texture(renderer, img_wajnberg, cell.x, cell.y, cell.w, cell.h);
                        else
                            SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255), SDL_RenderFillRect(renderer, &cell);
                    }
                } else if (c == KILLED_BOAT) {
                    if (player->character == 0) {
                        if (player->screen == 0)
                            render_texture(renderer, img_sananes1, cell.x, cell.y, cell.w, cell.h);
                        else
                            render_texture(renderer, img_wajnberg1, cell.x, cell.y, cell.w, cell.h);
                    } else {
                        if (player->screen == 0)
                            render_texture(renderer, img_wajnberg1, cell.x, cell.y, cell.w, cell.h);
                        else
                            render_texture(renderer, img_sananes1, cell.x, cell.y, cell.w, cell.h);
                    }
                } else {
                    switch (c) {
                        case WATER: SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255); break;
                        case SHOT_WATER: SDL_SetRenderDrawColor(renderer, 0, 50, 200, 255); break;
                        case SHOT_BOAT: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
                        default: SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255); break;
                    }
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }


        long elapsed = time(NULL) - timestamp;
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        char chrono_text[16];
        snprintf(chrono_text, sizeof(chrono_text), "%02d:%02d", minutes, seconds);
        int tw, th;
        TTF_SizeText(font, chrono_text, &tw, &th);
        render_text(renderer, chrono_text, (width - tw)/2, height - th - 20, font, white);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyTexture(img_sananes);
    SDL_DestroyTexture(img_sananes1);
    SDL_DestroyTexture(img_wajnberg);
    SDL_DestroyTexture(img_wajnberg1);
    return SELECT_NONE;
}


