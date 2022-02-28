#include "bmp_parser.h"

int bmp_to_static_texture(const char *file_name, const int bmp_channels, SDL_Renderer *renderer, SDL_Texture **static_texture, Uint32 tex_format)
{
    Sint8 *content;
    if (open_file(file_name, &content)) return -1;

    Sint32 width, height;
    bmp_dim(content, &width, &height);

    Sint32 row_size = width * bmp_channels;
    Sint32 padded_row_size = calc_padded_row(row_size);

    Sint8 *head = start_point(content);
    Sint8 *pixels = SDL_malloc(width*height*bmp_channels);
    if (!pixels)
    {
        SDL_Log("Pixels allocation failure : %s", SDL_GetError());
        return -1;
    }

    *static_texture = SDL_CreateTexture(renderer, tex_format, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!*static_texture)
    {
        SDL_Log("Texture creation failure : %s", SDL_GetError());
        SDL_free(pixels);
        return -1;
    }

    for (Sint32 y=0; y<height; y++)
    {
        SDL_memcpy(pixels+(height-y-1)*row_size,
                   head+y*padded_row_size,
                   row_size);
    }

    SDL_UpdateTexture(*static_texture, NULL, pixels, row_size);
    SDL_free(pixels);
    return 0;
}

Sint8 *start_point(Sint8 *content)
{
    Sint32 *offset = (Sint32*)(content+10);
    return content + *offset;
}

Sint32 calc_padded_row(const Sint32 row_size)
{
    Sint32 padded_row_size = (row_size / alignment) * alignment;
    if (row_size % alignment) padded_row_size += alignment;
    return padded_row_size;
}

void bmp_dim(const Sint8 *content, Sint32 *w, Sint32 *h)
{
    SDL_memcpy(w, content+18, 4);
    SDL_memcpy(h, content+22, 4);
}

int open_file(const char* file_name, Sint8 **content)
{
    SDL_RWops *file = SDL_RWFromFile(file_name, "rb");
    if (!file)
    {
        SDL_Log("File open failure : %s", SDL_GetError());
        return -1;
    }

    Sint64 file_size = SDL_RWsize(file);
    *content = SDL_malloc(file_size);
    if (!*content)
    {
        SDL_Log("Allocation failure : %s", SDL_GetError());
        SDL_RWclose(file);
        return -1;
    }

    SDL_RWread(file, *content, file_size, 1);
    SDL_RWclose(file);
    return 0;
}