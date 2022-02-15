#include "bomberman.h"

int level_init(level_t *level, const uint32_t cols, const uint32_t rows, const uint32_t cell_size, int32_t *cells)
{
    if (!level || !cols || !rows || !cell_size)
        return -1;

    level->cols = cols;
    level->rows = rows;
    level->cell_size = cell_size;
    level->cells = cells;
    return 0;
}

int32_t level_cell(level_t *level, const uint32_t col, const uint32_t row)
{
    if (!level->cells)
        return -1;
    if (col >= level->cols)
        return -1;
    if (row >= level->rows)
        return -1;

    return level->cells[row * level->cols + col];
}

void draw_level(SDL_Renderer *renderer, level_t level, SDL_Rect cell_rect)
{
    for (uint32_t row = 0; row < level.rows; row++)
    {
        for (uint32_t col = 0; col < level.cols; col++)
        {
            int32_t cell = level_cell(&level, col, row);
            int32_t cell_texture = cell & 0xff;
            cell_rect.x = col * level.cell_size;
            cell_rect.y = row * level.cell_size;

            if (cell_texture == BLOCK_GROUND)
            {
                SDL_SetRenderDrawColor(renderer, 90, 93, 16, 255);
                SDL_RenderFillRect(renderer, &cell_rect);
            }
            else if (cell_texture == BLOCK_WALL)
            {
                SDL_SetRenderDrawColor(renderer, 52, 52, 52, 255);
                SDL_RenderFillRect(renderer, &cell_rect);
            }
            else if (cell_texture == BLOCK_DESTROYABLE)
            {
                SDL_SetRenderDrawColor(renderer, 0, 50, 50, 255);
                SDL_RenderFillRect(renderer, &cell_rect);
            }
        }
    }
}