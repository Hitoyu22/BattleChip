#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
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
} Board;

void init_board(Board *board, int width, int height)
{
    board->width = width;
    board->height = height;
    board->grid = malloc(height * sizeof(TILE *));
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
}

void hardboat(Board *board)
{
    place_boat_on_board(board, 0, 0, 5, HORIZONTAL);
    place_boat_on_board(board, 6, 0, 4, VERTICAL);
    place_boat_on_board(board, 0, 2, 3, HORIZONTAL);
    place_boat_on_board(board, 8, 0, 3, VERTICAL);
    place_boat_on_board(board, 0, 4, 2, HORIZONTAL);
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

int can_place_ship(Board *board, int row, int col, int ship_size, int direction)
{
    return is_valid_placement(board, col, row, ship_size, (direction == 0) ? HORIZONTAL : VERTICAL);
}

void place_ship(Board *board, int row, int col, int ship_size, int direction)
{
    place_boat_on_board(board, col, row, ship_size, (direction == 0) ? HORIZONTAL : VERTICAL);
}

int place_ship_randomly(Board *board, int ship_size)
{
    int attempts = 0;
    while (attempts < 100)
    {
        int row = rand() % 10;
        int col = rand() % 10;
        int direction = rand() % 2;

        if (can_place_ship(board, row, col, ship_size, direction))
        {
            place_ship(board, row, col, ship_size, direction);
            return 1;
        }
        attempts++;
    }
    return 0;
}

void place_ships_randomly(Board *board, int nb_navires)
{
    int ship_sizes[] = {5, 4, 3, 3, 2, 4, 3, 2, 2};
    char *ship_names[] = {"Porte-avions", "Croiseur", "Destroyer 1", "Destroyer 2", "Torpilleur", "Navire 6", "Navire 7", "Navire 8", "Navire 9"};

    srand(time(NULL));
    printf("aleatoire...\n");

    for (int i = 0; i < nb_navires; i++)
    {
        if (place_ship_randomly(board, ship_sizes[i]))
        {
            printf("✓ %s placé\n", ship_names[i]);
        }
        else
        {
            printf("✗%s\n", ship_names[i]);
        }
    }

    printf("\nfianle\n");
    print_board(board);
}

int main()
{
    int board_width = 10;
    int board_height = 10;
    Board board;

    int nb_navires;
    printf("cmb navires (min: 1, max: 9): ");
    scanf("%d", &nb_navires);

    if (nb_navires < 1)
    {
        nb_navires = 1;
        printf(" fixé à 1.\n");
    }
    else if (nb_navires > 9)
    {
        nb_navires = 9;
        printf(" fixé à 9.\n");
    }

    init_board(&board, board_width, board_height);
    printf("%dx%d\n", board_width, board_height);
    printf("Nbr navires à placer: %d\n\n", nb_navires);

    int choice;
    printf("Mode de placement:\n");
    printf("1. Manuel\n");
    printf("2. Aléatoire\n");
    printf("Choix: ");
    scanf("%d", &choice);

    while (getchar() != '\n')
        ;

    if (choice == 2)
    {
        place_ships_randomly(&board, nb_navires);
    }
    else
    {
        place_ships_manually(&board, nb_navires);
    }

    free_board(&board);
    return 0;
}
