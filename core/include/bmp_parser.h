#pragma once
#include <SDL.h>

static const Sint32 alignment = 4;
static const Sint32 channels = 4;

int bmp_to_static_texture(const char *file_name, const int bmp_channels, SDL_Renderer *renderer, SDL_Texture **static_texture, Uint32 tex_format);
int open_file(const char* file_name, Sint8 **content);
Sint32 calc_padded_row(const Sint32 row_size);
void bmp_dim(const Sint8 *content, Sint32 *w, Sint32 *h);
Sint8 *start_point(Sint8 *content);