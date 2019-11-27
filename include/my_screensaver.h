/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** my_screensaver .h file
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include "graph.h"

#ifndef MY_SCREENSAVER_H_
#define MY_SCREENSAVER_H_

#define MSG_INVALID_ARG_NBR "Invalid arguments number\n"
#define EXIT_INVALID_ARG_NBR 84
#define MSG_INVALID_ARG_TYPE "The first argument isn't a number\n"
#define EXIT_INVALID_ARG_TYPE 84
#define MSG_ANIM_ID_ERROR "The second number isn't an animation\n"
#define EXIT_ANIM_ID_ERROR 84

#define MAX_ID 2
#define NBR_COLORS 0xffffffff

#endif


#ifndef DOTS_TRAIL_H_
#define DOTS_TRAIL_H_

#define DOTS_NBR 10
#define MAX_RADIUS 200

typedef struct dots_s
{
    int x;
    int y;
    int radius;
    int max_radius;
    int *blacklist_radius;
    int blacklist_radius_size;
    sfColor color;
} dots_t;

int does_kill_prog(sfRenderWindow *window, int game_id);
int dots_trail(assets_t *assets, int game_id);

void free_dots(dots_t *dots);
int *insert_tab_value(int *tab, int radius, int size);
void reset_dot_pos(dots_t *dot);

#endif


#ifndef GAME_OF_LIFE_H_
#define GAME_OF_LIFE_H_

#define CELL_NBR 200000
#define CELL_DEAD sfBlack
#define CELL_INCIPIENT sfGreen
#define CELL_ALIVE sfBlue
#define CELL_ONE_TIME sfYellow
#define CELL_DYING sfRed

int game_of_life(assets_t *assets, int game_id);
bool is_eq_color(sfColor color1, sfColor color2);
int count_alive_cells(bool **board, unsigned int x, unsigned int y);
void free_board(bool **board);

#endif