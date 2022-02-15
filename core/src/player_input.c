#include "player_input.h"

void movement_input(SDL_Event event, bomberman_t player, float *d_right, float *d_left, float *d_down, float *d_up)
{
    if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    *d_right = player.movable.speed * (1.0 / 60);
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    *d_left = -player.movable.speed * (1.0 / 60);
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    *d_down = player.movable.speed * (1.0 / 60);
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    *d_up = -player.movable.speed * (1.0 / 60);
                }
            }
            if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    *d_right = 0;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    *d_left = 0;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    *d_down = 0;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    *d_up = 0;
                }
            }
}