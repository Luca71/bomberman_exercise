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

void draw_level(SDL_Renderer *renderer, SDL_Texture *level_cell_tex, level_t level, SDL_Rect cell_rect)
{
    /* Ground texture */
    const char *ground_block_tex_name = "assets/BackgroundTile.bmp";
    const char *solid_block_tex_name = "assets/SolidBlock.bmp";

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
                int result = bmp_to_static_texture(ground_block_tex_name, 3, renderer, &level_cell_tex, SDL_PIXELFORMAT_BGR24);
                if (result == -1) SDL_free(level_cell_tex);
            }
            else if (cell_texture == BLOCK_WALL)
            {
                int result = bmp_to_static_texture(solid_block_tex_name, 3, renderer, &level_cell_tex, SDL_PIXELFORMAT_BGR24);
                if (result == -1) SDL_free(level_cell_tex);
            }
            else if (cell_texture == BLOCK_DESTROYABLE)
            {
                SDL_SetRenderDrawColor(renderer, 0, 50, 50, 255);
                SDL_RenderFillRect(renderer, &cell_rect);
            }

            SDL_SetTextureBlendMode(level_cell_tex, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, level_cell_tex, NULL, &cell_rect);   
        }
    }
}