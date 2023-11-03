#include "gui.h"

#include "color.h"
#include "display.h"

#ifdef SIMULATE_ON_PC
    #include "sdl_wrapper.h"

uint8_t vram_array[DISPLAY_SIZE];
#endif

void gui_sync() {
#ifdef SIMULATE_ON_PC
    sdl_sync();
#else
    // TODO
#endif
}

void gui_init() {
#ifdef SIMULATE_ON_PC
    sdl_init();
    vram = (uint8_t *)vram_array;
#else
    // TODO
#endif
    for (int i = 0; i < DISPLAY_HEIGHT; ++i) {
        for (int j = 0; j < DISPLAY_WIDTH; ++j) {
#ifdef SIMULATE_ON_PC
            VRAM(i, j) = BLACK;
#else
    // TODO
#endif
        }
    }
    gui_sync();
}