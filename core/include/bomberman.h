#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <stdint.h>
#include <SDL.h>
#include "bmp_parser.h"

#define BLOCK_MASK_UNWALKABLE 0x0100
#define BLOCK_MASK_TELEPORT 0x0200
#define BLOCK_MASK_EXIT 0x0400

#define BLOCK_GROUND 0
#define BLOCK_WALL 1
#define BLOCK_DESTROYABLE 2

typedef struct level
{
    int32_t *cells;     // content of the level
    uint32_t cols;      // number of columns of the level grid
    uint32_t rows;      // number of rows of the level grid
    uint32_t cell_size; // size in pixel of a single cell
} level_t;

typedef struct movable
{
    float x;
    float y;
    uint32_t width;
    uint32_t height;
    float speed;
} movable_t;

typedef struct bomberman
{
    movable_t movable;
    uint32_t id;
    uint32_t number_of_bombs;
    uint32_t dropped_bombs;
    uint32_t bomb_power;
} bomberman_t;

/*
 * Move a movable_t obj into the level map checking for collision
 *
 * @param level The level map
 * @param movable The obj to move
 * @param delta_x Delta movement on X axis
 * @param delta_y Delta movement on Y axis
 * @return The cell on which the obj stop in
*/
int32_t move_on_level(level_t* level, movable_t* movable, const float delta_x, const float delta_y);

/*
 * Init the level map
 *
 * @param level The level map to be initialized
 * @param cols Number of columns in the level map
 * @param rows Number of rows in the level map
 * @param cell_size Dimension of one cell inside map (square cell)
 * @param cells The cells map for the level
 * @return -1 if something go wrong
*/
int level_init(level_t *level, const uint32_t cols, const uint32_t rows, const uint32_t cell_size, int32_t *cells);

/*
 * Get the cell at given coordinates
 *
 * @param level The level map to be initialized
 * @param col Number of column in the level map
 * @param row Number of row in the level map
 * @return The cell where the obj is in, or -1 if something go wrong
*/
int32_t level_cell(level_t* level, const uint32_t col, const uint32_t row);

/*
 * Draw the level
 *
 * @param renderer The level renderer
 * @param level_cell_tex The texture for lvel cells
 * @param level Thew level to draw
 * @param cell_rect The cell rect reference
*/
void draw_level(SDL_Renderer *renderer, SDL_Texture *level_cell_tex, level_t level, SDL_Rect cell_rect);

/*
 * Get the id of a player
 *
 * @param player A player in game
 * @return The id the given player
*/
int movable_get_id(bomberman_t *player);

/*
 * Get the current x position of a player
 *
 * @param player A player in game
 * @return The x position of the given player
*/
float movable_get_x(bomberman_t *player);

/*
 * Get the current y position of a player
 *
 * @param player A player in game
 * @return The y position of the given player
*/
float movable_get_y(bomberman_t *player);

#endif //BOMBERMAN_H