/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** my_screensaver .h file
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include "graph.h"

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

bool does_kill_prog(sfRenderWindow *window);
int dots_trail(assets_t *assets);

void free_dots(dots_t *dots);
int *insert_tab_value(int *tab, int radius, int size);
void reset_dot_pos(dots_t *dot);

#endif

#ifndef MY_SCREENSAVER_H_
#define MY_SCREENSAVER_H_

#define MSG_INVALID_ARG_NBR "Invalid arguments number\n"
#define EXIT_INVALID_ARG_NBR 84
#define MSG_INVALID_ARG_TYPE "The first argument isn't a number"
#define EXIT_INVALID_ARG_TYPE 84
#define EXIT_ERROR 84

#define MAX_ID 1
#define NBR_COLORS 0xffffffff

#endif