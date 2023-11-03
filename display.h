#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480

#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)

#define COLOR_BACKGROUND 0x000000FF
#define COLOR_FOREGROUND 0x406060FF

extern uint8_t *vram;
#define VRAM(x, y) vram[(x)*DISPLAY_WIDTH + (y)]

#endif
