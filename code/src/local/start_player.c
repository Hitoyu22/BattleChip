#include "./../../include/sdl/sdl_utils.h"
#include "./../../include/sdl/music.h"

int show_player_choice(int player, int *character, int *choice_position, SDL_Renderer *renderer) {
    int running = 1;
    SDL_Event event;

    const int width = 1000;
    int result = 0;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray  = {50, 50, 50, 255};

    TTF_Font *title_font  = load_font("./assets/fonts/font.ttf", 48);
    TTF_Font *button_font = load_font("./assets/fonts/font.ttf", 28);

    SDL_Texture *img_sananes   = load_texture(renderer, "./assets/images/sananes.png");
    SDL_Texture *img_wajnberg  = load_texture(renderer, "./assets/images/wajnberg.png");

    SDL_Texture *btn_sananes_img  = resize_texture(renderer, img_sananes, 150, 150);
    SDL_Texture *btn_wajnberg_img = resize_texture(renderer, img_wajnberg, 150, 150);

    SDL_Rect btn_sananes  = { width / 4 - 75, 600, 150, 200 };
    SDL_Rect btn_wajnberg = { 3 * width / 4 - 75, 600, 150, 200 };

    init_audio();
    playSong("./assets/music/perso.mp3");

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    result = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                        result = 0;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x;
                        int my = event.button.y;

                        if (mx >= btn_sananes.x && mx <= btn_sananes.x + btn_sananes.w &&
                            my >= btn_sananes.y && my <= btn_sananes.y + btn_sananes.h) {
                            *character = 0;
                            running = 0;
                            result = 1;
                        }

                        if (mx >= btn_wajnberg.x && mx <= btn_wajnberg.x + btn_wajnberg.w &&
                            my >= btn_wajnberg.y && my <= btn_wajnberg.y + btn_wajnberg.h) {
                            *character = 1;
                            running = 0;
                            result = 1;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
        SDL_RenderClear(renderer);

        char title_text[100];
        snprintf(title_text, sizeof(title_text), "Joueur %d, sélectionnez votre personnage", player);
        int tw, th;
        TTF_SizeText(title_font, title_text, &tw, &th);
        render_text(renderer, title_text, (width - tw) / 2, 100, title_font, white);

        render_texture(renderer, btn_sananes_img, btn_sananes.x, btn_sananes.y, 150, 150);
        render_button(renderer, &(SDL_Rect){btn_sananes.x, btn_sananes.y + 150, 150, 50}, "Sananes", white, gray, button_font);

        render_texture(renderer, btn_wajnberg_img, btn_wajnberg.x, btn_wajnberg.y, 150, 150);
        render_button(renderer, &(SDL_Rect){btn_wajnberg.x, btn_wajnberg.y + 150, 150, 50}, "Wajnberg", white, gray, button_font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    running = 1;
    int th,tw;
    int btn_width_manual = 150;
    int btn_width_auto   = 250;
    SDL_Rect btn_manual    = { width / 4 - btn_width_manual/2, 500, btn_width_manual, 75 };
    SDL_Rect btn_automatic = { 3 * width / 4 - btn_width_auto/2, 500, btn_width_auto, 75 };

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    result = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                        result = 0;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x;
                        int my = event.button.y;

                        if (mx >= btn_manual.x && mx <= btn_manual.x + btn_manual.w &&
                            my >= btn_manual.y && my <= btn_manual.y + btn_manual.h) {
                            *choice_position = 0; 
                            running = 0;
                        }

                        if (mx >= btn_automatic.x && mx <= btn_automatic.x + btn_automatic.w &&
                            my >= btn_automatic.y && my <= btn_automatic.y + btn_automatic.h) {
                            *choice_position = 1; 
                            running = 0;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        const char *mode_text = "Choisissez votre mode d'insertion des bateaux";
        TTF_SizeText(title_font, mode_text, &tw, &th);
        render_text(renderer, mode_text, (width - tw) / 2, 100, title_font, white);

        render_button(renderer, &btn_manual, "Manuel", white, gray, button_font);
        render_button(renderer, &btn_automatic, "Automatique", white, gray, button_font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(img_sananes);
    SDL_DestroyTexture(img_wajnberg);
    SDL_DestroyTexture(btn_sananes_img);
    SDL_DestroyTexture(btn_wajnberg_img);
    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);

    return result;
}

