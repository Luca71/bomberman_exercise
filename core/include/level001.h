#pragma once
#include <stdint.h>

typedef struct color
{
    int8_t r;
    int8_t g;
    int8_t b;
    int8_t a;
} color_t;

int32_t level001_cells[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x101, 0, 0x101, 0, 0x101, 0x101, 0,
    0, 0, 0, 0x101, 0, 0, 0, 0,
    0, 0x101, 0, 0x101, 0, 0x101, 0x101, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x101, 0x101, 0, 0, 0, 0x101, 0,
    0, 0x101, 0x101, 0, 0x101, 0, 0x101, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};