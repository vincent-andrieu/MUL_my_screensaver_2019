/*
** EPITECH PROJECT, 2019
** CSFML
** File description:
** display an image in a window
*/

#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include <fcntl.h>
#include <time.h>
#include "my.h"
#include "graph.h"
#include "my_screensaver.h"

static bool is_key_released(sfKeyCode key)
{
    while (sfKeyboard_isKeyPressed(key)) {
        if (!sfKeyboard_isKeyPressed(key))
            return true;
    }
    return false;
}

bool does_kill_prog(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) {
            sfRenderWindow_close(window);
            return true;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft)
        || sfKeyboard_isKeyPressed(sfKeyRight))
            return true;
    }
    return false;
}

static int show_window(assets_t *assets, int game_id)
{
    sfEvent event;
    int (*game_list[2])(assets_t *) = {dots_trail, game_of_life};

    srand(time(NULL));
    game_list[game_id - 1](assets);
    while (sfRenderWindow_pollEvent(assets->window, &event)) {
        if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(assets->window);
        if (is_key_released(sfKeyLeft))
            game_id = game_id <= 0 ? MAX_ID : game_id - 1;
        else if (is_key_released(sfKeyRight))
            game_id = game_id >= MAX_ID ? 0 : game_id + 1;
    }
    sfTexture_updateFromPixels(assets->texture, assets->framebuffer->pixels,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
    sfRenderWindow_clear(assets->window, sfBlack);
    sfRenderWindow_drawSprite(assets->window, assets->sprite, NULL);
    sfRenderWindow_display(assets->window);
    return game_id;
}

int prepare_window(int game_id)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    assets_t *assets = malloc(sizeof(assets_t));
    assets->window = sfRenderWindow_create(mode, "MyScreensaver",
                                                    sfResize | sfClose, NULL);
    assets->texture = sfTexture_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    assets->sprite = sfSprite_create();
    assets->framebuffer = framebuffer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (assets->window == NULL || assets->texture == NULL)
        return EXIT_FAILURE;
    sfSprite_setTexture(assets->sprite, assets->texture, sfTrue);
    sfRenderWindow_setFramerateLimit(assets->window, 30);
    while (sfRenderWindow_isOpen(assets->window))
        game_id = show_window(assets, game_id);
    framebuffer_destroy(assets->framebuffer);
    sfSprite_destroy(assets->sprite);
    sfTexture_destroy(assets->texture);
    sfRenderWindow_destroy(assets->window);
    free(assets);
    return 0;
}

int main(int argc, char **argv)
{
    int game_id;

    if (argc != 2) {
        my_put_error_str(MSG_INVALID_ARG_NBR);
        return EXIT_INVALID_ARG_NBR;
    }
    if (my_str_isnum(argv[1])) {
        game_id = my_getnbr(argv[1]);
        if (game_id >= 1 && game_id <= MAX_ID)
            return prepare_window(game_id);
        my_put_error_str(MSG_ANIM_ID_ERROR);
        return EXIT_ANIM_ID_ERROR;
    }
    my_put_error_str(MSG_INVALID_ARG_TYPE);
    return EXIT_INVALID_ARG_TYPE;
}