#ifndef SNAKE_H_
#define SNAKE_H_

#include "map.h"
#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} Position;

typedef struct {
    uint16_t head, tail;
    Position pos[GRID_TOTAL];
} Snake;

typedef enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    STAY_STILL,
} Movement;

typedef enum {
    ALIVE,
    DEAD,
} SnakeState;

void snake_init(Snake *s, Map *m);

uint16_t snake_lenght(Snake *s);

SnakeState snake_move(Snake *s, Map *m, Movement move);

#endif