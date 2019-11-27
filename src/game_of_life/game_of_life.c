/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** game of life
*/

#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include "graph.h"
#include "my_screensaver.h"

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

int game_of_life(assets_t *assets, int game_id)
{
    bool **board = create_rand_map();
    int const last_game_id = game_id;

    if (board == NULL)
        return EXIT_FAILURE;
    while (game_id == last_game_id) {
        run_cells(assets, board);
        kill_cells(assets->framebuffer, board);
        game_id = does_kill_prog(assets->window, game_id);
    }
    free_board(board);
    return game_id;
}
