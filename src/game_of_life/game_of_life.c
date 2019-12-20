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
        my_draw_rect(framebuffer, (sfVector2f) {x, y},
            (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_INCIPIENT);
    else if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_INCIPIENT))
        my_draw_rect(framebuffer, (sfVector2f) {x, y},
            (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_ALIVE);
}

static void put_dead(framebuffer_t *framebuffer, unsigned int x,
                        unsigned int y)
{
    if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_INCIPIENT))
        my_draw_rect(framebuffer, (sfVector2f) {x, y},
            (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_ONE_TIME);
    else if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_ALIVE))
        my_draw_rect(framebuffer, (sfVector2f) {x, y},
            (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_DYING);
}

static void run_cells(assets_t *assets, bool **board)
{
    int nbr_alives;

    for (unsigned int x = 0; x < WINDOW_WIDTH; x += CELL_SIZE)
        for (unsigned int y = 0; y < WINDOW_HEIGHT; y += CELL_SIZE) {
            nbr_alives = count_alive_cells(board, x, y);
            if (nbr_alives == 3)
                put_alive(assets->framebuffer, x, y);
            else if (nbr_alives < 2 || nbr_alives > 3)
                put_dead(assets->framebuffer, x, y);
            if (nbr_alives != 3 && (nbr_alives == 2 || nbr_alives == 3)
            && is_eq_color(my_get_pixel_color(assets->framebuffer, x, y),
            CELL_INCIPIENT))
                my_draw_rect(assets->framebuffer, (sfVector2f) {x, y},
                    (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_ALIVE);
        }
    refresh_screen(assets);
}

static void kill_cells(framebuffer_t *framebuffer, bool **board)
{
    for (unsigned int x = 0; x < WINDOW_WIDTH; x += CELL_SIZE)
        for (unsigned int y = 0; y < WINDOW_HEIGHT; y += CELL_SIZE) {
            if (is_eq_color(my_get_pixel_color(framebuffer, x, y), CELL_DYING)
            || is_eq_color(my_get_pixel_color(framebuffer, x, y),
                            CELL_ONE_TIME))
                my_draw_rect(framebuffer, (sfVector2f) {x, y},
                    (sfVector2f) {CELL_SIZE, CELL_SIZE}, CELL_DEAD);
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
    fill_background(assets->framebuffer, CELL_DEAD);
    while (game_id == last_game_id) {
        run_cells(assets, board);
        kill_cells(assets->framebuffer, board);
        game_id = does_kill_prog(assets->window, game_id);
    }
    free_board(board);
    return game_id;
}
