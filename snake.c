
#include "snake.h"

#include <stdbool.h>
#include <stdint.h>

#include "map.h"
#include "random.h"

void snake_init(Snake *s, Map *m) {
    s->tail = 0;
    s->head = 1;
    uint8_t x = GRID_VERTICAL_NUM / 2;
    uint8_t y = GRID_HORIZONTAL_NUM / 2;
    s->pos[0].x = x;
    s->pos[0].y = y;
    m->grids[x][y] = SNAKE;
    map_draw(m);
}

uint16_t snake_lenght(Snake *s) {
    return (s->head - s->tail + GRID_TOTAL) % GRID_TOTAL;
}

static void snake_push_front(Snake *s, Position pos) {
    s->pos[s->head] = pos;
    s->head = (s->head + 1 + GRID_TOTAL) % GRID_TOTAL;
}

static void snake_pop_back(Snake *s) {
    s->tail = (s->tail + 1 + GRID_TOTAL) % GRID_TOTAL;
}

static Position snake_head(Snake *s) {
    return s->pos[(s->head - 1 + GRID_TOTAL) % GRID_TOTAL];
}

static Position snake_tail(Snake *s) {
    return s->pos[s->tail];
}

SnakeState snake_move(Snake *s, Map *m, Movement move) {
    Position head = snake_head(s);
    static const uint16_t direction[][2] =
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    uint16_t x = head.x + direction[move][0];
    uint16_t y = head.y + direction[move][1];
    // eat the food?
    if (m->grids[x][y] == FOOD) {
        map_update_food(m);
    } else {
        Position tail = snake_tail(s);
        m->grids[tail.x][tail.y] = NOTHING;
        snake_pop_back(s);
    }
    // hit the wall?
    if (x < 0 || x >= GRID_VERTICAL_NUM || y < 0 || y >= GRID_HORIZONTAL_NUM) {
        return DEAD;
    }
    // hit itself?
    uint16_t i = s->tail;
    while (i != s->head) {
        if (x == s->pos[i].x && y == s->pos[i].y) {
            return DEAD;
        }
        i = (i + 1 + GRID_TOTAL) % GRID_TOTAL;
    }
    Position pos = {
        .x = x,
        .y = y,
    };
    snake_push_front(s, pos);
    m->grids[x][y] = SNAKE;
    map_draw(m);
    return ALIVE;
}
