#include "map.h"

#include <stdint.h>

#include "color.h"
#include "display.h"
#include "gui.h"
#include "random.h"

void map_init(Map *m) {
    for (int i = 0; i < GRID_VERTICAL_NUM; ++i) {
        for (int j = 0; j < GRID_HORIZONTAL_NUM; ++j) {
            m->grids[i][j] = NOTHING;
        }
    }
}

void map_update_food(Map *m) {
    for (;;) {
        uint8_t x = generate_random_num() % GRID_VERTICAL_NUM;
        uint8_t y = generate_random_num() % GRID_HORIZONTAL_NUM;
        if (m->grids[x][y] == NOTHING) {
            m->grids[x][y] = FOOD;
            break;
        }
    }
    map_draw(m);
}

void map_draw(Map *m) {
    for (uint16_t i = 0; i < DISPLAY_HEIGHT; ++i) {
        for (uint16_t j = 0; j < DISPLAY_WIDTH; ++j) {
            uint16_t x = i / (DISPLAY_HEIGHT / GRID_VERTICAL_NUM);
            uint16_t y = j / (DISPLAY_WIDTH / GRID_HORIZONTAL_NUM);
            ColorType color = BLACK;
            GridType grid = m->grids[x][y];
            if (grid == SNAKE) {
                color = BLUE;
            } else if (grid == FOOD) {
                color = GREEN;
            }
            VRAM(i, j) = color;
        }
    }
}