#define CLOVE_SUITE_NAME MovableTest
#include "clove-experimental.h"
#include "../include/bomberman.h"

CLOVE_TEST(MovableFixPositionX)                    
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = { 1, 0, 4, 4};
    move_on_level(&level, &movable, -10, 0);
    CLOVE_FLOAT_EQ(movable.x, 0);
}
CLOVE_TEST(MovableFixPositionY)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = { 1, 0, 4, 4};
    move_on_level(&level, &movable, 0, -30);
    CLOVE_FLOAT_EQ(movable.y, 0);
}
CLOVE_TEST(MovableFixPositionWidth)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = { 1, 0, 4, 4};
    move_on_level(&level, &movable, 50, 0);
    CLOVE_FLOAT_EQ(movable.x, 28);
}
CLOVE_TEST(MovableFixPositionHeight)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 2, 2, 8, map);
    movable_t movable = { 1, 1, 4, 4};
    move_on_level(&level, &movable, 0, 20);
    CLOVE_FLOAT_EQ(movable.y, 12);
}

CLOVE_TEST(MovableRightWallHitX)                        // Move right
{
    level_t level;
    int32_t map[] = {0, 0x101, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 1, 1, 32, 32};
    move_on_level(&level, &movable, 80, 0);
    CLOVE_FLOAT_EQ(movable.x, 32);
}
CLOVE_TEST(MovableRightWallHitYNeck)
{
    level_t level;
    int32_t map[] = {0, 0x101, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 16, 48, 32, 32};
    move_on_level(&level, &movable, 80, 0);
    CLOVE_FLOAT_EQ(movable.x, 32);
}
CLOVE_TEST(MovableRightWallHitYFeet)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0x101};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 16, 48, 32, 32};
    move_on_level(&level, &movable, 80, 0);
    CLOVE_FLOAT_EQ(movable.x, 32);
}

CLOVE_TEST(MovableLeftWallHitX)                         // Move left
{
    level_t level;
    int32_t map[] = {0x101, 0, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 80, 16, 32, 32};
    move_on_level(&level, &movable, -80, 0);
    CLOVE_FLOAT_EQ(movable.x, 64);
}
CLOVE_TEST(MovableLeftWallHitYNeck)
{
    level_t level;
    int32_t map[] = {0x101, 0, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 80, 48, 32, 32};
    move_on_level(&level, &movable, -80, 0);
    CLOVE_FLOAT_EQ(movable.x, 64);
}
CLOVE_TEST(MovableLeftWallHitYFeet)
{
    level_t level;
    int32_t map[] = {0, 0, 0x101, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 80, 48, 32, 32};
    move_on_level(&level, &movable, -80, 0);
    CLOVE_FLOAT_EQ(movable.x, 64);
}

CLOVE_TEST(MovableDownWallHitY)                        // Move down
{
    level_t level;
    int32_t map[] = {0, 0, 0x101, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 16, 16, 32, 32};
    move_on_level(&level, &movable, 0, 80);
    CLOVE_FLOAT_EQ(movable.y, 32);
}
CLOVE_TEST(MovableDownWallHitYLeftSide)                        
{
    level_t level;
    int32_t map[] = {0, 0, 0x101, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 48, 16, 32, 32};
    move_on_level(&level, &movable, 0, 80);
    CLOVE_FLOAT_EQ(movable.y, 32);
}
CLOVE_TEST(MovableDownWallHitYRightSide)                        
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0x101};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 48, 16, 32, 32};
    move_on_level(&level, &movable, 0, 80);
    CLOVE_FLOAT_EQ(movable.y, 32);
}

CLOVE_TEST(MovableUpWallHitY)                        // Move up
{
    level_t level;
    int32_t map[] = {0x101, 0, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 16, 80, 32, 32};
    move_on_level(&level, &movable, 0, -80);
    CLOVE_FLOAT_EQ(movable.y, 64);
}
CLOVE_TEST(MovableUpWallHitYLeftSide)                        
{
    level_t level;
    int32_t map[] = {0x101, 0, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 48, 80, 32, 32};
    move_on_level(&level, &movable, 0, -80);
    CLOVE_FLOAT_EQ(movable.y, 64);
}
CLOVE_TEST(MovableUpWallHitYRightSide)                        
{
    level_t level;
    int32_t map[] = {0, 0x101, 0, 0};
    level_init(&level, 2, 2, 64, map);
    movable_t movable = { 48, 80, 32, 32};
    move_on_level(&level, &movable, 0, -80);
    CLOVE_FLOAT_EQ(movable.y, 64);
}