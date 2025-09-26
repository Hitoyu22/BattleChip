#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int posInBoat(Boat * boat, int x, int y);

char killBoat(Boat * boat, Board * board);

char attack(Board * board, int posX, int posY);

char isEnd(Boat ** boats, int nbBoat);

#endif