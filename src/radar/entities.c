/*
** EPITECH PROJECT, 2019
** my_screensaver
** File description:
** manage entities
*/

#include <stdlib.h>
#include "graph.h"
#include "my_screensaver.h"

static entities_t **add_entity(entities_t **entities, int x, int y)
{
    entities_t **temp = entities;
    int size = 0;

    for (; entities[size] != NULL; size++);
    entities = malloc(sizeof(entities_t *) * (size + 2));
    if (entities == NULL)
        return NULL;
    for (int i = 0; temp[i] != NULL; i++)
        entities[i] = temp[i];
    free(temp);
    entities[size] = malloc(sizeof(entities_t));
    if (entities[size] == NULL)
        return NULL;
    *entities[size] = (entities_t) {x, y,
        ENTITY_RADIUS_MIN + rand() % (ENTITY_RADIUS_MAX - ENTITY_RADIUS_MIN),
        200};
    entities[size + 1] = NULL;
    return entities;
}

static void delete_entity_index(entities_t **entities, int index)
{
    int i = 0;

    for (; entities[i + 1] != NULL; i++)
        if (i >= index) {
            if (i == index)
                free(entities[i]);
            entities[i] = entities[i + 1];
        }
    entities[i] = NULL;
}

void fade_entities(framebuffer_t *framebuffer, entities_t **entities)
{
    for (int i = 0; entities[i] != NULL; i++) {
        my_draw_batman(framebuffer, (sfVector2f) {entities[i]->x,
            entities[i]->y}, entities[i]->radius,
            (sfColor) {entities[i]->opacity, entities[i]->opacity, 0, 255});
        entities[i]->opacity -= 2;
        if (entities[i]->opacity <= 0)
            delete_entity_index(entities, i);
    }
}

entities_t **get_entity(scan_t **scans, entities_t **entities)
{
    int rand_x;
    int const spawn_index = ENTITY_SPAWN_INDEX >= SCAN_FADE_SIZE
                            ? SCAN_FADE_SIZE - 1 : ENTITY_SPAWN_INDEX;

    rand_x = scans[spawn_index]->dest_x > WINDOW_WIDTH / 2 ?
        (WINDOW_WIDTH / 2 + rand()
        % (scans[spawn_index]->dest_x - WINDOW_WIDTH / 2))
        : (rand() % (WINDOW_WIDTH / 2));
    return add_entity(entities, rand_x,
        WINDOW_HEIGHT / 2 + (scans[spawn_index]->dest_y - WINDOW_HEIGHT / 2)
        * (rand_x - WINDOW_WIDTH / 2)
        / (scans[spawn_index]->dest_x - WINDOW_WIDTH / 2));
}

entities_t **create_entities(void)
{
    entities_t **entities = malloc(sizeof(entities_t *));

    if (entities == NULL)
        return NULL;
    entities[0] = NULL;
    return entities;
}