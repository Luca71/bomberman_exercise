#include <SDL.h>
#include <time.h>
#include "bomberman.h"
#include "level001.h"
#include "player_input.h"
#include "client.h"

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
    player0.movable.height = 32;
    player0.movable.speed = 48;

    /* Create client socket */
    int _socket = client_init_socket();
    struct sockaddr_in sin;
    client_set_socket_address(&sin, LOCAL_HOST);


    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Bomberman",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          level001.cols * level001.cell_size,
                                          level001.rows * level001.cell_size,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect cell_rect = {0, 0, level001.cell_size, level001.cell_size};

    SDL_Rect player0_rect = {0, 0, player0.movable.width, player0.movable.height};

    float delta_right = 0;
    float delta_left = 0;
    float delta_down = 0;
    float delta_up = 0;

    /* Timer variable */

    time_t start_time;
    _time64(&start_time);

    int running = 1;
    while (running)
    {   
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            
            movement_input(event, player0, &delta_right, &delta_left, &delta_down, &delta_up);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        draw_level(renderer, level001, cell_rect);
        
        move_on_level(&level001, &player0.movable, delta_right + delta_left, delta_down + delta_up);
        player0_rect.x = player0.movable.x;
        player0_rect.y = player0.movable.y;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player0_rect);

        /* send packet every 2 second */
        time_t counter;
        _time64(&counter);
        if(counter > start_time + PACKET_SEND_DELAY)
        {
            client_send_packet(_socket, sin, movable_get_id(&player0), movable_get_x(&player0), movable_get_y(&player0), 12);
            start_time = counter;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}