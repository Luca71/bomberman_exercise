#pragma once
#include <SDL.h>
#include "bomberman.h"

/*
 * Takes inputs and move player accordling
 *
 * @param event The event to handle
 * @param player The player i need to move
 * @param d_right The delta moment on right axis
 * @param d_left The delta moment on left axis
 * @param d_down The delta moment on down axis
 * @param d_up The delta moment on up axis
*/
void movement_input(SDL_Event event, bomberman_t player, float *d_right, float *d_left, float *d_down, float *d_up);