/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** dots trail function
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "graph.h"
#include "my_screensaver.h"

void reset_dot_pos(dots_t *dot)
{
    free(dot->blacklist_radius);
    dot->blacklist_radius = malloc(sizeof(int));
    if (dot->blacklist_radius == NULL)
        return;
    dot->blacklist_radius_size = 1;
    dot->max_radius = rand() % (MAX_RADIUS - 1) + 1;
    dot->radius = (int) rand() % dot->max_radius;
    dot->x = dot->radius
                + rand() % (WINDOW_WIDTH - (dot->radius + 5) * 2);
    dot->y = dot->radius
                + rand() % (WINDOW_HEIGHT - (dot->radius + 5) * 2);
    dot->color = sfColor_fromInteger(rand() % NBR_COLORS);
}

int *insert_tab_value(int *tab, int radius, int size)
{
    int *result = malloc(sizeof(int) * (size + 1));

    if (result == NULL)
        return NULL;
    for (int i = 0; i < size; i++)
        result[i] = tab[i];
    free(tab);
    result[size] = radius;
    return result;
}

void free_dots(dots_t *dots)
{
    for (int i = 0; i < DOTS_NBR; i++)
        free(dots[i].blacklist_radius);
    free(dots);
}