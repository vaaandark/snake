#ifndef SDL_WRAPPER_H_
#define SDL_WRAPPER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void sdl_sync();
void sdl_init();
void sdl_drop();

#endif
