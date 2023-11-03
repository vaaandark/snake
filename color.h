#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

#define RGB256_BLACK 0x000000ff
#define RGB256_BLUE 0x0000ffff
#define RGB256_GREEN 0x008000ff

typedef enum: uint8_t {
    BLACK,
    BLUE,
    GREEN,
} ColorType;

#endif