#include "sdl_wrapper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>

#include "color.h"
#include "display.h"

#define MAX_TEXT 100

SDL_Window *window;
SDL_Renderer *renderer;

static uint32_t get_color(ColorType color) {
    switch (color) {
        case BLACK:
            return RGB256_BLACK;
        case BLUE:
            return RGB256_BLUE;
        case GREEN:
            return RGB256_GREEN;
    }
    return -1;
}

void sdl_init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT,
        SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void sdl_set_color(uint32_t color) {
    SDL_SetRenderDrawColor(
        renderer,
        color >> 24,
        color >> 16,
        color >> 8,
        color);
}

void sdl_draw_rectangle(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

void sdl_fill_rectangle(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void sdl_sync() {
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            uint32_t color = get_color(VRAM(i, j));
            sdl_set_color(color);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
}

void sdl_drop() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
