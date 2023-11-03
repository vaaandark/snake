#ifndef MAP_H_
#define MAP_H_

#include <stdint.h>

#define GRID_HORIZONTAL_NUM 16u
#define GRID_VERTICAL_NUM 16u
#define GRID_TOTAL (GRID_HORIZONTAL_NUM * GRID_VERTICAL_NUM)

typedef enum {
    NOTHING,
    SNAKE,
    FOOD,
} GridType;

typedef struct {
    GridType grids[GRID_VERTICAL_NUM][GRID_HORIZONTAL_NUM];
} Map;

void map_init(Map *m);

void map_update_food(Map *m);

void map_draw(Map *m);

#endif