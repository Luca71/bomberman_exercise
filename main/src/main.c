#include <SDL.h>
#include <time.h>
#include "bomberman.h"
#include "level001.h"
#include "player_input.h"
#include "client.h"
#include "bmp_parser.h"
#include "player_mgr.h"

#define LOCAL_HOST "127.0.0.1"
#define PACKET_SEND_DELAY 2


int main(int argc, char **argv)
{
    /* Init level */
    level_t level001;
    level_init(&level001, 8, 8, 64, level001_cells);

    /* Create Player and his start position */
    bomberman_t player0;
    player0.id = 100;
    player0.movable.x = 140;
    player0.movable.y = 140;
    player0.movable.width = 32;
    player0.movable.height = 64;
    player0.movable.speed = PLAYER_SPEED;

    /* Create client socket */
    int _socket = client_init_socket();
    struct sockaddr_in sin;
    client_set_socket_address(&sin, LOCAL_HOST);

    /* Init game window */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bomberman",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          level001.cols * level001.cell_size,
                                          level001.rows * level001.cell_size,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    /* init players list */
    player_vector_t *players_list = player_mgr_new_vector();

    /* Player texture and rect */
    char *texture_player_file_name = "assets/Bman_F_f00.bmp";
    SDL_Texture *player_texture;
    SDL_Rect player_rect = {0, 0, player0.movable.width, player0.movable.height};
    int result = bmp_to_static_texture(texture_player_file_name, 4, renderer, &player_texture, SDL_PIXELFORMAT_BGRA32);
    if (result == -1) goto quit;
    SDL_SetTextureBlendMode(player_texture, SDL_BLENDMODE_BLEND);

    /* Level cell texture and rect */
    SDL_Texture *level_cell_tex;
    SDL_Rect cell_rect = {0, 0, level001.cell_size, level001.cell_size};

    /* Init player delta movement */
    float delta_right = 0;
    float delta_left = 0;
    float delta_down = 0;
    float delta_up = 0;

    /* Timer variable */
    time_t start_time;
    _time64(&start_time);

    // Game loop
    int running = 1;
    while (running)
    {   
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
                printf("Quit");
            }
            
            movement_input(event, player0, &delta_right, &delta_left, &delta_down, &delta_up);
        }

        /* Clear the window */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        /* Draw level */
        draw_level(renderer, level_cell_tex, level001, cell_rect);
        
        /* Move local player */
        move_on_level(&level001, &player0.movable, delta_right + delta_left, delta_down + delta_up);
        player_rect.x = player0.movable.x;
        player_rect.y = player0.movable.y;
        
        /* Draw local player */
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);

        /* send and receive packet every 2 seconds */
        time_t counter;
        _time64(&counter);
        char msg_content[12];
        char msg_in[12];

        if(counter > start_time + PACKET_SEND_DELAY)
        {
            client_send_packet(_socket, sin, movable_get_id(&player0), movable_get_x(&player0), movable_get_y(&player0), 12);
            start_time = counter;
            client_receive_packet(_socket, sin, msg_in);

            /* check if message is from a new player */
            player_mgr_find_player(players_list, msg_in);
        }

        if(players_list->count > 0)
        {
            /* update player position from players list */
            player_mgr_update_transform(players_list, msg_in);

            /* draw players */
            player_rect.x = players_list[0].item.movable.x;
            player_rect.y = players_list[0].item.movable.y;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);
        }

        SDL_RenderPresent(renderer);
    }

quit:
    if (level_cell_tex) SDL_DestroyTexture(level_cell_tex); 
    if (player_texture) SDL_DestroyTexture(player_texture); 
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}