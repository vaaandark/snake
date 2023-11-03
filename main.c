#include <stdbool.h>
#include <stdint.h>

#include "display.h"
#include "gui.h"
#include "map.h"
#include "snake.h"

#define INTERVAL 200

#ifdef SIMULATE_ON_PC
    #include <SDL2/SDL_events.h>
    #include <SDL2/SDL_keycode.h>

    #include "sdl_wrapper.h"
#endif

#ifdef SIMULATE_ON_PC
Map map;
Snake snake;
#else
// TODO
#endif

int main(void) {
#ifdef SIMULATE_ON_PC
    gui_init();
start_entry:
    map_init(&map);
    snake_init(&snake, &map);
    map_update_food(&map);
    gui_sync();
    bool alive = true;
    Movement move = STAY_STILL;
    SDL_Event event;
    while (alive) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                alive = false;
            } else {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_r) {
                        goto start_entry;
                    } else if (event.key.keysym.sym == SDLK_q) {
                        alive = false;
                    } else {
                        switch (event.key.keysym.sym) {
                            case SDLK_w:
                            case SDLK_UP:
                                if (move != DOWN) {
                                    move = UP;
                                }
                                break;
                            case SDLK_s:
                            case SDLK_DOWN:
                                if (move != UP) {
                                    move = DOWN;
                                }
                                break;
                            case SDLK_a:
                            case SDLK_LEFT:
                                if (move != RIGHT) {
                                    move = LEFT;
                                }
                                break;
                            case SDLK_d:
                            case SDLK_RIGHT:
                                if (move != LEFT) {
                                    move = RIGHT;
                                }
                                break;
                        }
                    }
                }
            }
        }
        if (alive) {
            alive = snake_move(&snake, &map, move) == ALIVE;
        }
        if (alive) {
            gui_sync();
        }
        SDL_Delay(INTERVAL);
    }
    sdl_drop();

#else
#endif
}
