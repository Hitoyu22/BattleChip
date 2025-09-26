#include <stdio.h>
#include <stdlib.h>
#include "../../include/board.h"
#include "../../include/interaction.h"
#include "../../include/config.h"

typedef struct
{
    int row, col;
} Position;

Board ** initGame(){
    Config * config = initConfig();
    Board ** tab = malloc(sizeof(Board*)*2);
    
    for(int i = 0; i++<2;) {
        Boat ** boats = malloc(sizeof(Boat*));
        init_board(tab[i],config->GRID_WIDTH,config->GRID_HEIGHT, 0, boats);
    }
    return tab;
}

int main()
{   
    Board * board = boardCreation();
    printf("%d\n",attack(board,1,1));
    printf("%d\n",attack(board,0,0));
    print_board(board);
    free(board);
    return 0;
}