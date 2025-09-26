#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "navire.h"

typedef struct
{
    int row, col;
} Position;

typedef struct Board
{
    int width;
    int height;
    TILE **grid;
    Boat ** boats;
    int nbBoat;
} Board;

void init_board(Board *board, int width, int height, int nbNavire, Boat ** boats);

void print_board(Board *board);

void place_boat_on_board(Board *board, int x, int y, int length, Orientation orientation);

void free_board(Board *board);

int parse_position(const char *pos, int *x, int *y);

int is_valid_placement(Board *board, int x, int y, int length, Orientation orientation);

void place_ships_manually(Board *board, int nb_navires);

Board * boardCreation();

#endif