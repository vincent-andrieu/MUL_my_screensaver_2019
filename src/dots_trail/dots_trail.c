/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** dots trail
*/

#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include <math.h>
#include "graph.h"
#include "my_screensaver.h"

static int rand_radius(dots_t *dot, int n)
{
    if (n > dot->max_radius / 2) {
        reset_dot_pos(dot);
        return dot->radius;
    }
    dot->radius = rand() % dot->max_radius;
    for (int i = 0; i < dot->blacklist_radius_size; i++)
        if (dot->radius == dot->blacklist_radius[i]) {
            return rand_radius(dot, ++n);
        }
    dot->blacklist_radius = insert_tab_value(dot->blacklist_radius, dot->radius,
                                            dot->blacklist_radius_size);
    dot->blacklist_radius_size++;
    return dot->radius;
}

static float change_angle(float angle, dots_t *dots, assets_t *assets)
{
    angle -= 10.0;
    if (angle <= 0) {
        for (int i = 0; i < DOTS_NBR; i++)
            dots[i].radius = rand_radius(&dots[i], 0);
        sfTexture_updateFromPixels(assets->texture, assets->framebuffer->pixels,
                                    WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
        sfRenderWindow_drawSprite(assets->window, assets->sprite, NULL);
        sfRenderWindow_display(assets->window);
        return 360;
    }
    return angle;
}

static void trail(assets_t *assets, dots_t *dots)
{
    float angle = 360;
    float x;
    float y;

    while (!does_kill_prog(assets->window)) {
        for (int i = 0; i < DOTS_NBR; i++) {
            x = dots[i].radius * cos(angle * M_PI / 180);
            y = dots[i].radius * sin(angle * M_PI / 180);
            my_draw_rect(assets->framebuffer,
                (sfVector2f) {dots[i].x + x, dots[i].y + y},
                (sfVector2f) {5, 5}, dots[i].color);
        }
        angle = change_angle(angle, dots, assets);
    }
}

static dots_t *create_dots(void)
{
    dots_t *dots = malloc(sizeof(dots_t) * DOTS_NBR);

    if (dots == NULL)
        return NULL;
    for (int i = 0; i < DOTS_NBR; i++) {
        dots[i].blacklist_radius = malloc(sizeof(int));
        if (dots[i].blacklist_radius == NULL)
            return NULL;
        dots[i].blacklist_radius_size = 1;
        dots[i].max_radius = rand() % (MAX_RADIUS - 1) + 1;
        dots[i].radius = rand() % dots[i].max_radius;
        dots[i].blacklist_radius[0] = dots[i].radius;
        dots[i].x = dots[i].radius
                    + rand() % (WINDOW_WIDTH - (dots[i].radius + 5) * 2);
        dots[i].y = dots[i].radius
                    + rand() % (WINDOW_HEIGHT - (dots[i].radius + 5) * 2);
        dots[i].color = sfColor_fromInteger(rand() % NBR_COLORS);
    }
    return dots;
}

int dots_trail(assets_t *assets)
{
    dots_t *dots = create_dots();

    if (dots == NULL)
        return EXIT_FAILURE;
    trail(assets, dots);
    free_dots(dots);
    return 0;
}