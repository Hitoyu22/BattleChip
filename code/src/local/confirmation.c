#include "./../../include/sdl/sdl_utils.h"

int show_confirmation(int player_id, SDL_Renderer *renderer) {
    int running = 1;
    SDL_Event event;
    int result = 0;

    const int width = 1000, height = 1000;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray  = {80, 80, 80, 255};

    TTF_Font *title_font  = load_font("./assets/fonts/font.ttf", 48);
    TTF_Font *button_font = load_font("./assets/fonts/font.ttf", 32);

    SDL_Rect btn_ready = { width/2 - 100, height/2, 200, 80 };

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
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
                        if (mx >= btn_ready.x && mx <= btn_ready.x + btn_ready.w &&
                            my >= btn_ready.y && my <= btn_ready.y + btn_ready.h) {
                            result = 1;
                            running = 0;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        char title[100];
        snprintf(title, sizeof(title), "Joueur %d, êtes-vous prêt ?", player_id);
        int tw, th;
        TTF_SizeText(title_font, title, &tw, &th);
        render_text(renderer, title, (width - tw) / 2, height/3, title_font, white);

        render_button(renderer, &btn_ready, "Prêt !", white, gray, button_font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);

    return result;
}
