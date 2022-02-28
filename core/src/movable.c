#include "bomberman.h"

int32_t move_on_level(level_t *level, movable_t *movable, const float delta_x, const float delta_y)
{
    float new_x = movable->x + delta_x;
    float new_y = movable->y + delta_y;
    float half_height = movable->height * 0.5;

    // Check window bounds
    if (new_x < 0)
        new_x = 0;
    else if (new_x + movable->width >= level->cols * level->cell_size)
        new_x = (level->cols * level->cell_size) - movable->width;

    if (new_y < 0)
        new_y = 0;
    else if (new_y + movable->height >= level->rows * level->cell_size)
        new_y = (level->rows * level->cell_size) - movable->height;

    int32_t cell = -1;
    // moving right ?
    if (new_x > movable->x)
    {
        uint32_t cell_x = (new_x + movable->width - 1) / level->cell_size; // cell on which the movable will end
        uint32_t cell_y = (movable->y + movable->height - 1) / level->cell_size; // test for feet
        cell = level_cell(level, cell_x, cell_y);
        if (cell & BLOCK_MASK_UNWALKABLE) // collision!
        {
            movable->x = cell_x * level->cell_size - movable->width; // bring back
        }
        else
        {
            cell_y = (movable->y + half_height - 1) / level->cell_size; // test for neck
            cell = level_cell(level, cell_x, cell_y);
            if (cell & BLOCK_MASK_UNWALKABLE) // collision!
            {
                movable->x = cell_x * level->cell_size - movable->width; // bring back
            }
            else
            {
                movable->x = new_x;
            }
        }
    }

    // moving left ?
    else if (new_x < movable->x)
    {
        uint32_t cell_x = new_x / level->cell_size; // cell on which the movable will end
        uint32_t cell_y = (movable->y + movable->height - 1) / level->cell_size; // test for feet
        cell = level_cell(level, cell_x, cell_y);
        if (cell & BLOCK_MASK_UNWALKABLE) // collision!
        {
            movable->x = (cell_x * level->cell_size) + level->cell_size;
        }
        else
        {
            cell_y = (movable->y + half_height - 1) / level->cell_size; // test for neck
            cell = level_cell(level, cell_x, cell_y);
            if (cell & BLOCK_MASK_UNWALKABLE) // collision!
            {
                movable->x = (cell_x * level->cell_size) + level->cell_size;
            }
            else
            {
                movable->x = new_x;
            }
        }
    }

    // moving down ?
    else if(new_y > movable->y)
    {
        uint32_t cell_x = movable->x / level->cell_size; // test the left side
        uint32_t cell_y = (new_y + movable->height - 1) / level->cell_size;
        cell = level_cell(level, cell_x, cell_y);
        if (cell & BLOCK_MASK_UNWALKABLE)
        {
            movable->y = (cell_y * level->cell_size) - movable->height;
        }
        else
        {
            cell_x = (movable->x + movable->width -1) / level->cell_size; // test the right side
            cell = level_cell(level, cell_x, cell_y);
            if (cell & BLOCK_MASK_UNWALKABLE) // collision!
            {
                movable->y = (cell_y * level->cell_size) - movable->height;
            }
            else
            {
                movable->y = new_y;
            }
        }
    }

    // moving up ?
    else if(new_y < movable->y)
    {
        uint32_t cell_x = movable->x / level->cell_size; // test the left side
        uint32_t cell_y = (new_y + half_height - 1) / level->cell_size;
        cell = level_cell(level, cell_x, cell_y);
        if (cell & BLOCK_MASK_UNWALKABLE)
        {
            movable->y = (cell_y * level->cell_size) + half_height + 1;
        }
        else
        {
            cell_x = (movable->x + movable->width - 1) / level->cell_size; // test the right side
            cell = level_cell(level, cell_x, cell_y);
            if (cell & BLOCK_MASK_UNWALKABLE) // collision!
            {
                movable->y = (cell_y * level->cell_size) + half_height + 1;
            }
            else
            {
                movable->y = new_y;
            }
        }
    }

    return cell;
}

int movable_get_id(bomberman_t *player)
{
    return player->id;
}

float movable_get_x(bomberman_t *player)
{
    return player->movable.x;
}

float movable_get_y(bomberman_t *player)
{
    return player->movable.y;
}