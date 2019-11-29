/*
** EPITECH PROJECT, 2019
** CSFML
** File description:
** display an image in a window
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <fcntl.h>
#include <time.h>
#include "my.h"
#include "graph.h"
#include "my_screensaver.h"

int does_kill_prog(sfRenderWindow *window, int game_id)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyReleased
        && event.key.code == sfKeyEscape)) {
            sfRenderWindow_close(window);
            return 0;
        }
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyLeft)
            return game_id <= 1 ? MAX_ID : game_id - 1;
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyRight)
            return game_id >= MAX_ID ? 1 : game_id + 1;
    }
    return game_id;
}

static void clear_screen(assets_t *assets)
{
    for (unsigned int i = 0;
    i < assets->framebuffer->width * assets->framebuffer->height * 4; i++)
        assets->framebuffer->pixels[i] = 0;
}

static int show_window(assets_t *assets, int game_id)
{
    sfEvent event;
    int (*game_list[3])(assets_t *, int) = {dots_trail, game_of_life, radar};

    srand(time(NULL));
    fill_background(assets->framebuffer, BACKGROUND_COLOR);
    game_id = game_list[game_id - 1](assets, game_id);
    while (sfRenderWindow_pollEvent(assets->window, &event))
        if (game_id < 1 || game_id > MAX_ID || event.type == sfEvtClosed
        || sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(assets->window);
    clear_screen(assets);
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