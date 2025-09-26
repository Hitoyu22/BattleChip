#include <stdio.h>
#include <stdlib.h>
#include "../../include/board.h"


int posInBoat(Boat * boat, int x, int y){
    for(int i =0; i < boat->taille; i++){
        if (boat->orientation==HORIZONTAL) {
            if ((boat->x+i)==x && boat->y==y) return i;
        }
        else if (boat->orientation==VERTICAL) if (boat->x==x && (boat->y+i)==y) return i;
    }
    return -1;
}

char killBoat(Boat * boat, Board * board){
    int x = boat->x;
    int y = boat->y;
    for(int i =0; i<boat->taille; i++){
        if (boat->orientation==HORIZONTAL) board->grid[y][x+i] = KILLED_BOAT;
        else if (boat->orientation==HORIZONTAL) board->grid[y+i][x] = KILLED_BOAT;
    }
    boat->est_coule = 1;
    return 1;
}

char attack(Board * board/*, Boat ** bateaux*/, int posX, int posY){
    if ((board->grid)[posY][posX]==WATER) {
        (board->grid)[posY][posX]=SHOT_WATER;
        return 0;
    } else if ((board->grid)[posY][posX]==BOAT) {
        (board->grid)[posY][posX] = SHOT_BOAT;
        for (int i = 0; i<(board->nbBoat); i++){
            if (posInBoat((board->boats)[i],posX,posY)!=-1){
                (board->boats)[i]->etat[posInBoat((board->boats)[i],posX,posY)] = SHOT_BOAT;
                if (!isAlive((board->boats)[i])){
                    killBoat((board->boats)[i], board);
                }
            }
        }
        return 1;
    }
    return 0 ;
}

char isEnd(Boat ** boats){
    for (int i = 0; i < 5; i++){
        if (isAlive(boats[i])) return 0;
    }
    return 1;
}