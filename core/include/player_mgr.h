#pragma once
#include <SDL.h>
#include "bomberman.h"

#define NUM_OF_PLAYERS 4
#define BOMBS_NUM 3
#define BOMB_POWER 1
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 64
#define PLAYER_SPEED 60

typedef struct players_vector {
    uint32_t count;
    bomberman_t item;
} player_vector_t;

/*
 * Init a new vector of NUM_OF_PLAYERS players;
 *
 * @return A vector of players
*/
player_vector_t *player_mgr_new_vector();

/*
 * Free players list memory
*/
void player_mgr_list_free(player_vector_t *players_vector);

/*
 * Add a new player to the list
 *
 * @param vector The vector of players to add new player
 * @param id The new player id
*/
void player_mgr_add_player(player_vector_t *players_vector, uint32_t id);

/*
 * Get player index from players list
 *
 * @param vector The vector of players
 * @param id The player id
 * @return int index of the player with given id. -1 in case no player id found
*/
int player_mgr_get_player_index(player_vector_t *players_vector, uint32_t id);

/*
 * Set X and Y value of a given player
 *
 * @param vector The vector of players
 * @param id The player id
 * @param player_x The x value for the player
 * @param player_y The y value for the player
*/
void player_mgr_set_player_transform(player_vector_t *players_vector, uint32_t id, float player_x, float player_y);

/*
 * Search if the player is new or it already exist in the players list
 *
 * @param vector The vector of players
 * @param msg_content The message received from server
*/
void player_mgr_find_player(player_vector_t *players_vector, char *msg_content);

/*
 * Update the player transform received from server
 *
 * @param vector The vector of players
 * @param msg_content The message received from server
*/
void player_mgr_update_transform(player_vector_t *players_vector, char *msg_content);



