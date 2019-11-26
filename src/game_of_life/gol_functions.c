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

    for (unsigned int i = x - 1; i <= x + 1; i++) {
        for (unsigned int j = y - 1; j <= y + 1; j++)
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