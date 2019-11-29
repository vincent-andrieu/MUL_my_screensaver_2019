/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** radar
*/

#include <stdlib.h>
#include "graph.h"
#include "my_screensaver.h"

static void free_radar(scan_t **scans, entities_t **entities)
{
    int i = 0;

    for (; i < SCAN_FADE_SIZE; i++)
        free(scans[i]);
    for (i = 0; entities[i] != NULL; i++)
        free(entities[i]);
    free(entities[i]);
    free(entities);
}

int radar(assets_t *assets, int game_id)
{
    int const last_game_id = game_id;
    scan_t *scans[SCAN_FADE_SIZE];
    entities_t **entities = create_entities();

    if (entities == NULL)
        return EXIT_FAILURE;
    fill_scan_struct(scans);
    while (game_id == last_game_id) {
        scans_rot(assets->framebuffer, scans);
        if (rand() % 100 <= ENTITY_SPAWN_PERCENT) {
            entities = get_entity(scans, entities);
            if (entities == NULL)
                return EXIT_FAILURE;
        }
        fade_entities(assets->framebuffer, entities);
        refresh_screen(assets);
        game_id = does_kill_prog(assets->window, game_id);
    }
    free_radar(scans, entities);
    return game_id;
}