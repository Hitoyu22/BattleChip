#include "./../../include/local/start_player.h"
#include "./../../include/local/map.h"
#include "./../../include/local/place_boat.h"
#include "./../../include/local/confirmation.h"
#include "./../../include/local/game.h"
#include "./../../include/sdl/music.h"
#include "./../../include/core/board.h"
#include "./../../include/core/config.h"
#include "./../../include/core/interaction.h"
#include <time.h>




TILE **get_table(Player *p, TILE **table1, TILE **table2) {
    if (p->player_id == 1) {
        return (p->screen == 0) ? table1 : table2;
    } else {
        return (p->screen == 0) ? table2 : table1;
    }
}

void init_table(char ** table, int rows, int columns){

    for (int i = 0; i < rows; i++) {
        table[i] = malloc(sizeof(char) * columns);
        for (int j = 0; j < columns; j++) {
            table[i][j] = '.';
        }
    }
    return;
}

void start_solo_mode(SDL_Renderer *renderer) {


    Board ** board = initGame();

    printf("test3\n");

    Player player1 = {.player_id = 1, .screen = 1};
    Player player2 = {.player_id = 2, .screen = 1};

    printf("test3\n");
    printf("width : %d  height : %d\n", board[0]->width,board[0]->height);
    int rows = board[0]->width;
    int columns = board[0]->height;
    printf("test3\n");
    if (!show_player_choice(1, &player1.character, &player1.choice_position, renderer)) {
        printf("Joueur 1 a annulé, retour au menu.\n");
        
        free(board);
        
        return;
    }

        printf("test3\n");

    if (player1.choice_position == 0){
        printf("test\n");
        place_boats_visual(board[0], renderer);
    }
    else
        printf("Automatic\n");

    if (!show_player_choice(2, &player2.character, &player2.choice_position, renderer)) {
        printf("Joueur 2 a annulé, retour au menu.\n");
        freeGame(board);
        return;
    }

    if (player2.choice_position == 0)
        place_boats_visual(board[1], renderer);
    else
        printf("Automatic\n");

    printf("Joueur 1 = %d (mode %s), Joueur 2 = %d (mode %s)\n",
           player1.character, player1.choice_position ? "Auto" : "Manuel",
           player2.character, player2.choice_position ? "Auto" : "Manuel");

    Player *current = &player1;
    SelectedPosition position;
    int running = 1;
    long start_time = time(NULL);

    while (running) {

        printf("test 100\n");
        TILE **current_table = get_table(current, board[0]->grid, board[1]->grid);
        printf("test 100\n");

        int action = show_map(rows, columns, current_table, current,
                              renderer, start_time, &position);

                              printf("test 100\n");
        printf("test 101\n");
        if (action == SELECT_QUIT) {
            running = 0;

        } else if (action == SELECT_SWITCH) {
            current->screen = 1 - current->screen;
        printf("test 102\n");
        } else if (action == SELECT_CELL) {
            
            printf("pressé\n");
            if (attack(board[current->player_id%2], position.posX, position.posY)){

                if(isEnd(board[current->player_id%2]->boats, board[current->player_id%2]->nbBoat)){
                    printf("fini\n");
                }
            }

            printf("Joueur %d a sélectionné case (%d, %d)\n",
                   current->player_id, position.posX, position.posY);

            current = (current == &player1) ? &player2 : &player1;
            current->screen = 1;  

            if (!show_confirmation(current->player_id, renderer)) {
                printf("Joueur %d a quitté avant de jouer.\n", current->player_id);
                running = 0;
            }
        }
        printf("test 103\n");

        if (5 == 2){
            printf("Touché");
                init_audio();
                playSong("./assets/music/touche.mp3");
        }
        if (5 == 2){
            printf("Coulé");
                init_audio();
                playSong("./assets/music/coule.mp3");
        }
        if (5 == 2){
            printf("Eau");
                init_audio();
                playSong("./assets/music/eau.mp3");
        }

    }

    if (5 == 2){
        printf("Fin");
            init_audio();
            playSong("./assets/music/fin.mp3");
    }

    freeGame(board);
}


