#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../../include/sdl/sdl_utils.h"
#include "./../../include/local/place_boat.h"
#include "./../../include/core/board.h"

int place_boats_visual(Board * board, SDL_Renderer *renderer) {
    SDL_Event event;
    int start_x = 50, start_y = 50;

    int height = board->height;
    int width = board->width;
    int num_boats = board->nbBoat;
    int grid_size_x = (1000 - 2*start_x) / width;
    int grid_size_y = (1000 - 2*start_y) / height;
    int grid_size = (grid_size_x < grid_size_y) ? grid_size_x : grid_size_y;

    TTF_Font *font = load_font("./assets/fonts/font.ttf",24);
    SDL_Color white = {255,255,255,255};
    SDL_Color red = {255,0,0,255};
    SDL_Color yellow = {255,255,0,255};
    SDL_Color blue = {0,100,255,255};
    SDL_Color gray = {100,100,100,255};

    srand(time(NULL));

    for(int b=0;b<num_boats;b++){
        int length = board->boats[b]->taille;
        int placed = 0;
        int rotate = 0;
        int mx=0,my=0;
        int valid=1;

        while(!placed){
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        TTF_CloseFont(font);
                        return 0;

                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            if (valid) {
                                place_boat_on_board(board, mx, my, length, rotate ? VERTICAL : HORIZONTAL);    
                                placed = 1;
                            }
                        }
                        else if (event.button.button == SDL_BUTTON_RIGHT) {
                            rotate = !rotate;
                        }
                        break;

                    case SDL_MOUSEMOTION:
                        mx = (event.motion.x - start_x) / grid_size;
                        my = (event.motion.y - start_y) / grid_size;
                        break;
                }
            }

            valid = 1;
            for(int i=0;i<length;i++){
                int r = my + (rotate ? i : 0);
                int c = mx + (rotate ? 0 : i);
                if(r>=height || c>=width || board->grid[r][c] != WATER){
                    valid = 0;
                    break;
                }
            }

            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    SDL_Rect cell={start_x+j*grid_size,start_y+i*grid_size,grid_size-2,grid_size-2};
                    SDL_Color color;
                    if(board->grid[i][j] == BOAT) color = gray;
                    else color = blue;
                    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
                    SDL_RenderFillRect(renderer,&cell);
                }
            }

            for(int j=0;j<width;j++){
                char txt[2]={'A'+j,0};
                int tw,th;
                TTF_SizeText(font,txt,&tw,&th);
                render_text(renderer,txt,start_x+j*grid_size+(grid_size-tw)/2,start_y-40,font,white);
            }

            for(int i=0;i<height;i++){
                char txt[8];
                snprintf(txt,sizeof(txt),"%d",i+1);
                int tw,th;
                TTF_SizeText(font,txt,&tw,&th);
                render_text(renderer,txt,start_x-40+(40-tw)/2,start_y+i*grid_size+(grid_size-th)/2,font,white);
            }

            for(int i=0;i<length;i++){
                int r = my + (rotate ? i : 0);
                int c = mx + (rotate ? 0 : i);
                if(r<height && c<width){
                    SDL_Rect cell={start_x+c*grid_size,start_y+r*grid_size,grid_size-2,grid_size-2};
                    if(valid) SDL_SetRenderDrawColor(renderer,yellow.r,yellow.g,yellow.b,yellow.a);
                    else{
                        if((SDL_GetTicks()/300)%2) SDL_SetRenderDrawColor(renderer,red.r,red.g,red.b,red.a);
                        else SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    }
                    SDL_RenderFillRect(renderer,&cell);
                }
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }

    TTF_CloseFont(font);
    return 1;
}
