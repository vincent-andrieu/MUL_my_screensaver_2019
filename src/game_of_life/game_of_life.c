/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** game of life
** == 3 then ALIVE
** == 2 then NO_CHANGE
** < 2 || > 3 then DEAD
*/

#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include "graph.h"
#include "my_screensaver.h"

static bool is_eq_color(sfColor color1, sfColor color2)
{
    if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
        return true;
    return false;
}

static void put_alive(framebuffer_t *framebuffer, unsigned int x,
                        unsigned int y)
{
    if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_DEAD))
        my_put_pixel(framebuffer, x, y, CELL_INCIPIENT);
    else if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_INCIPIENT))
        my_put_pixel(framebuffer, x, y, CELL_ALIVE);
}

static void put_dead(framebuffer_t *framebuffer, unsigned int x,
                        unsigned int y)
{
    if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_INCIPIENT))
        my_put_pixel(framebuffer, x, y, CELL_ONE_TIME);
    else if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_ALIVE))
        my_put_pixel(framebuffer, x, y, CELL_DYING);
}

static int count_alive_cells(bool **board, unsigned int x, unsigned int y)
{
    int cells_alive = 0;

    for (unsigned int i = x - 1; i <= x + 1; i++) {
        for (unsigned int j = y - 1; j <= y + 1; j++)
            if (i < WINDOW_WIDTH && j < WINDOW_HEIGHT && board[i][j]
                && (i != x || j != y))
                cells_alive++;
    }
    return cells_alive;
}

static void run_cells(assets_t *assets, bool **board)
{
    int nbr_alives;

    for (unsigned int x = 0; x < WINDOW_WIDTH; x++)
        for (unsigned int y = 0; y < WINDOW_HEIGHT; y++) {
            nbr_alives = count_alive_cells(board, x, y);
            if (nbr_alives == 3)
                put_alive(assets->framebuffer, x, y);
            else if (nbr_alives < 2 || nbr_alives > 3)
                put_dead(assets->framebuffer, x, y);
            else if (is_eq_color(my_get_pixel_color(assets->framebuffer, x, y),
            CELL_INCIPIENT))
                my_put_pixel(assets->framebuffer, x, y, CELL_ALIVE);
        }
    sfTexture_updateFromPixels(assets->texture, assets->framebuffer->pixels,
                               WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
    sfRenderWindow_drawSprite(assets->window, assets->sprite, NULL);
    sfRenderWindow_display(assets->window);
}

static void kill_cells(framebuffer_t *framebuffer, bool **board)
{
    for (unsigned int x = 0; x < WINDOW_WIDTH; x++)
        for (unsigned int y = 0; y < WINDOW_HEIGHT; y++) {
            if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_DYING)
            || is_eq_color(my_get_pixel_color(framebuffer, x, y),
                            CELL_ONE_TIME))
                my_put_pixel(framebuffer, x, y, CELL_DEAD);
            board[x][y] = !is_eq_color(my_get_pixel_color(framebuffer, x, y),
                                        CELL_DEAD);
             }
}

static void free_tab(bool **board)
{
    for (int i = 0; i < WINDOW_WIDTH; i++)
        free(board[i]);
    free(board);
}

int game_of_life(assets_t *assets)
{
    bool **board = malloc(sizeof(bool *) * WINDOW_WIDTH);

    if (board == NULL)
        return EXIT_FAILURE;
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        board[i] = malloc(sizeof(bool) * WINDOW_HEIGHT);
        if (board[i] == NULL)
            return EXIT_FAILURE;
        for (int k = 0; k < WINDOW_HEIGHT; k++)
            board[i][k] = false;
    }
    for (int i = 0; i < CELL_NBR; i++)
        board[rand() % WINDOW_WIDTH][rand() % WINDOW_HEIGHT] = true;
    while (!does_kill_prog(assets->window)) {
        run_cells(assets, board);
        kill_cells(assets->framebuffer, board);
    }
    free_tab(board);
    return 0;
}
