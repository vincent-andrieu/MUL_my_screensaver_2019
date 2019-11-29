/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** manage scan
*/

#include <stdlib.h>
#include "graph.h"
#include "my_screensaver.h"

static int increase_rot(int a, int b, int const speed)
{
    a += b ? -speed : speed;
    if (a >= WINDOW_WIDTH)
        a = WINDOW_WIDTH;
    else if (a <= 0)
        a = 0;
    return a;
}

static void draw_line_size(framebuffer_t *framebuffer, scan_t *scans,
                            sfColor color, int size)
{
    for (int i = 0; i < size; i++) {
        my_draw_line(framebuffer,
            (sfVector2f) {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
            (sfVector2f) {scans->dest_x + i > WINDOW_WIDTH ? scans->dest_x :
            scans->dest_x + i, scans->dest_y + i}, color);
    }
}

void scans_rot(framebuffer_t *framebuffer, scan_t **scans)
{
    for (int i = 0; i < SCAN_FADE_SIZE; i++) {
        draw_line_size(framebuffer, scans[i],
            (sfColor) {0, 0, 0, SCAN_FADE_SIZE * 4 - scans[i]->color.a},
                                LINE_SIZE);
        if ((scans[i]->dest_x < WINDOW_WIDTH && scans[i]->dest_y <= 0)
            || (scans[i]->dest_x > 0 && scans[i]->dest_y >= WINDOW_HEIGHT))
            scans[i]->dest_x = increase_rot(scans[i]->dest_x, scans[i]->dest_y,
                                            DEF_SCAN_SPEED);
        else
            scans[i]->dest_y = increase_rot(scans[i]->dest_y, scans[i]->dest_x,
                                            -DEF_SCAN_SPEED);
        draw_line_size(framebuffer, scans[i], scans[i]->color, LINE_SIZE);
    }
}

void fill_scan_struct(scan_t **scans)
{
    for (int i = 0; i < SCAN_FADE_SIZE; i++) {
        scans[i] = malloc(sizeof(scan_t));
        scans[i]->dest_x = WINDOW_WIDTH / 2 - SCAN_FADE_SIZE + i;
        scans[i]->dest_y = 0;
        scans[i]->color = SCAN_COLOR;
    }
}