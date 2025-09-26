#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/core/navire.h"
#include "./../include/core/config.h"

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

void init_board(Board *board, int width, int height, int nbNavire, Boat ** boats)
{
    board->width = width;
    board->height = height;
    board->grid = malloc(height * sizeof(TILE *));
    board->boats = malloc(sizeof(Boat*)*nbNavire);
    printf("test25\n");
    board->nbBoat = nbNavire;

    Config * conf = initConfig();

    int tab[4] = {conf->SHIP_CARRIER, conf->SHIP_BATTLESHIP, conf->SHIP_DESTROYER, conf->SHIP_SUBMARINE};

    int tailles[nbNavire];
    int index = 0;

    for (int k = 0; k < 4; k++) {
        int ship_size;
        switch(k){
            case 0: ship_size = 5; break; 
            case 1: ship_size = 4; break; 
            case 2: ship_size = 3; break; 
            case 3: ship_size = 2; break; 
        }

        for (int i = 0; i < tab[k]; i++) {
            if (index >= nbNavire) {
                break;
            }
            tailles[index++] = ship_size;
        }
    }

    for (int i = 0; i<nbNavire; i++){
            printf("test26\n");
        board->boats[i] = malloc(sizeof(Boat));
            printf("test27\n");
            board->boats[i]=initBoat(-1,-1,HORIZONTAL,tailles[i],"");
        //cpBoat(board->boats[i],boats[i]);
            printf("test28\n");
    } 
    for (int i = 0; i < height; i++)
    {
        board->grid[i] = malloc(width * sizeof(TILE));
        for (int j = 0; j < width; j++)
        {
            board->grid[i][j] = WATER;
        }
    }
}

void print_board(Board *board)
{
    printf("    ");
    for (int j = 0; j < board->width; j++)
    {
        printf("%c   ", 'A' + j);
    }
    printf("\n");
    for (int i = 0; i < board->height; i++)
    {
        printf("%2d  ", i + 1);
        for (int j = 0; j < board->width; j++)
        {
            char symbol;
            switch (board->grid[i][j])
            {
            case WATER:
                symbol = '.';
                break;
            case BOAT:
                symbol = '#';
                break;
            case SHOT_WATER:
                symbol = 'O';
                break;
            case SHOT_BOAT:
                symbol = 'X';
                break;
            case KILLED_BOAT:
                symbol = '*';
                break;
            default:
                symbol = '.';
                break;
            }
            printf("%c   ", symbol);
        }
        printf("\n");
    }
}

void place_boat_on_board(Board *board, int x, int y, int length, Orientation orientation)
{
    board->nbBoat += 1;
    board->boats = realloc(board->boats, sizeof(Boat*)*board->nbBoat);
    board->boats[board->nbBoat-1] = malloc(sizeof(Boat));
    cpBoat(board->boats[board->nbBoat-1],initBoat(x,y,orientation,length,""));
    for (int i = 0; i < length; i++)
    {
        if (orientation == HORIZONTAL)
        {
            board->grid[y][x + i] = BOAT;
        }
        else
        {
            board->grid[y + i][x] = BOAT;
        }
    }

    print_board(board);


}

void free_board(Board *board)
{
    for (int i = 0; i < board->height; i++)
    {
        free(board->grid[i]);
    }
    free(board->grid);
}

int parse_position(const char *pos, int *x, int *y)
{
    if (strlen(pos) < 2)
        return 0;

    char col = toupper(pos[0]);
    if (col < 'A' || col > 'Z')
        return 0;

    *x = col - 'A';
    *y = atoi(&pos[1]) - 1;

    return 1;
}

int is_valid_placement(Board *board, int x, int y, int length, Orientation orientation)
{
    if (orientation == HORIZONTAL)
    {
        if (x + length > board->width || y >= board->height || x < 0 || y < 0)
            return 0;
    }
    else
    {
        if (y + length > board->height || x >= board->width || x < 0 || y < 0)
            return 0;
    }

    for (int i = 0; i < length; i++)
    {
        int check_x, check_y;
        if (orientation == HORIZONTAL)
        {
            check_x = x + i;
            check_y = y;
        }
        else
        {
            check_x = x;
            check_y = y + i;
        }

        if (board->grid[check_y][check_x] != WATER)
            return 0;
    }

    return 1;
}

void place_ships_manually(Board *board, int nb_navires)
{
    int ship_sizes[] = {5, 4, 3, 3, 2, 4, 3, 2, 2};
    char *ship_names[] = {"Porte-avions", "Croiseur", "Destroyer 1", "Destroyer 2", "Torpilleur", "Navire 6", "Navire 7", "Navire 8", "Navire 9"};

    printf("Format: Position (ex: B3) et direction (H pour horizontal, V pour vertical)\n");
    printf("Exemple: B3 H\n\n");

    for (int i = 0; i < nb_navires; i++)
    {
        int placed = 0;

        while (!placed)
        {

            printf("\n\n");
            print_board(board);

            printf("\nPlacez votre %s (%d cases)\n", ship_names[i], ship_sizes[i]);
            printf("(ex: B3) et(H/V): ");

            char input[20];
            char direction_char;

            if (fgets(input, sizeof(input), stdin) != NULL)
            {
                input[strcspn(input, "\n")] = 0;
                char position[10];
                if (sscanf(input, "%s %c", position, &direction_char) == 2)
                {
                    int x, y;
                    direction_char = toupper(direction_char);

                    if (direction_char != 'H' && direction_char != 'V')
                    {
                        printf(" H pour horizontal ou V pour vertical.\n");
                        continue;
                    }

                    Orientation orientation = (direction_char == 'H') ? HORIZONTAL : VERTICAL;
                    if (!parse_position(position, &x, &y))
                    {
                        printf("format lettre-chiffre (ex: B3).\n");
                        continue;
                    }

                    if (!is_valid_placement(board, x, y, ship_sizes[i], orientation))
                    {
                        printf("sort du plateau ou chevauche\n");
                        continue;
                    }

                    place_boat_on_board(board, x, y, ship_sizes[i], orientation);
                    printf("✓ %s\n", ship_names[i]);
                    placed = 1;
                }
                else
                {
                    printf("Position Direction (ex: B3 H)\n");
                }
            }
        }
    }
    printf("finale:\n");
    print_board(board);
}
Board * boardCreationConsole(){
    int board_width = 10;
    int board_height = 10;
    Board * board = malloc(sizeof(Board));

    int nb_navires;
    printf("cmb navires (min: 2, max: 9): ");
    scanf("%d", &nb_navires);

    if (nb_navires < 2)
    {
        nb_navires = 2;
        printf(" fixé à 2.\n");
    }
    else if (nb_navires > 9)
    {
        nb_navires = 9;
        printf(" fixé à 9.\n");
    }
    Boat ** navires = malloc(sizeof(Boat*)); 

    init_board(board, board_width, board_height,0,navires);
    printf("%dx%d\n", board_width, board_height);
    printf("Nbr navires à placer: %d\n\n", nb_navires);
    place_ships_manually(board, nb_navires);

    //free_board(board);
    return board;
}

Board * boardCreation(){
    int board_width = 10;
    int board_height = 10;
    Board * board = malloc(sizeof(Board));

    int nb_navires;
    printf("cmb navires (min: 2, max: 9): ");
    scanf("%d", &nb_navires);

    if (nb_navires < 2)
    {
        nb_navires = 2;
        printf(" fixé à 2.\n");
    }
    else if (nb_navires > 9)
    {
        nb_navires = 9;
        printf(" fixé à 9.\n");
    }
    Boat ** navires = malloc(sizeof(Boat*)); 

    init_board(board, board_width, board_height,0,navires);
    printf("%dx%d\n", board_width, board_height);
    printf("Nbr navires à placer: %d\n\n", nb_navires);
    place_ships_manually(board, nb_navires);

    //free_board(board);
    return board;
}


Board ** initGame(){
    Config * config = initConfig();
    Board ** tab = malloc(sizeof(Board*)*2);

    int totalShip = 0;
    totalShip+=config->SHIP_CARRIER;
    totalShip+=config->SHIP_BATTLESHIP;
    totalShip+=config->SHIP_DESTROYER;
    totalShip+=config->SHIP_SUBMARINE;


    printf("%d %d\n", config->GRID_WIDTH, config->GRID_HEIGHT);
    
    for(int i = 0; i<2; i++) {
        Boat ** boats = malloc(sizeof(Boat*)*totalShip);
        tab[i] = malloc(sizeof(Board));
        printf("test\n");
        init_board(tab[i],config->GRID_WIDTH,config->GRID_HEIGHT, totalShip, boats);
        printf("test\n");

        printf("boat %d, width: %d, hz=: %d\n", i, tab[i]->width, tab[i]->height);
    }
    return tab;
}


void freeGame(Board ** tab){
    for (int i =0 ; i<2;i++){
        free_board(tab[i]);
    }
    free(tab);
}