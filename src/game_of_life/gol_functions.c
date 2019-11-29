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

bool is_eq_color(sfColor color1, sfColor color2)
{
    if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
        return true;
    return false;
}

int count_alive_cells(bool **board, unsigned int x, unsigned int y)
{
    int cells_alive = 0;

    for (unsigned int i = x - CELL_SIZE; i <= x + CELL_SIZE; i += CELL_SIZE) {
        for (unsigned int j = y - CELL_SIZE; j <= y + CELL_SIZE; j += CELL_SIZE)
            if (i < WINDOW_WIDTH && j < WINDOW_HEIGHT && board[i][j]
                && (i != x || j != y))
                cells_alive++;
    }
    return cells_alive;
}

void free_board(bool **board)
{
    for (int i = 0; i < WINDOW_WIDTH; i++)
        free(board[i]);
    free(board);
}

bool **create_rand_map(void)
{
    bool **board = malloc(sizeof(bool *) * WINDOW_WIDTH);

    if (board == NULL)
        return NULL;
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        board[i] = malloc(sizeof(bool) * WINDOW_HEIGHT);
        if (board[i] == NULL)
            return NULL;
        for (int k = 0; k < WINDOW_HEIGHT; k++)
            board[i][k] = false;
    }
    for (int i = 0; i < CELL_NBR; i++)
        board[rand() % (WINDOW_WIDTH / CELL_SIZE) * CELL_SIZE]
            [rand() % (WINDOW_HEIGHT / CELL_SIZE) * CELL_SIZE] = true;
    return board;
}

void fill_background(framebuffer_t *framebuffer, sfColor color)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++)
        for (int x = 0; x < WINDOW_WIDTH; x++)
            my_put_pixel(framebuffer, x, y, color);
}