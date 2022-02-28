#include "player_mgr.h"

player_vector_t *player_mgr_new_vector()
{
    player_vector_t *players = malloc(sizeof(player_vector_t) * NUM_OF_PLAYERS);
    players->count = 0;
    return players;
}

void player_mgr_list_free(player_vector_t *players_vector)
{
    players_vector->count = 0;
    players_vector->item.movable.height = 0;
    players_vector->item.movable.width = 0;
    players_vector->item.movable.speed = 0;
    players_vector->item.movable.x = 0;
    players_vector->item.movable.y = 0;
    players_vector->item.bomb_power = 0;
    players_vector->item.number_of_bombs = 0;
    players_vector->item.dropped_bombs = 0;
    players_vector->item.id = 0;
    free(players_vector);
}

void player_mgr_add_player(player_vector_t *players_vector, uint32_t id)
{
    uint32_t index = players_vector->count;
    players_vector[index].item.id = id;
    players_vector[index].item.number_of_bombs = BOMBS_NUM;
    players_vector[index].item.bomb_power = BOMB_POWER;
    players_vector[index].item.dropped_bombs = 0;
    players_vector[index].item.movable.height = PLAYER_HEIGHT;
    players_vector[index].item.movable.width = PLAYER_WIDTH;
    players_vector[index].item.movable.speed = PLAYER_SPEED;
    players_vector[index].item.movable.x = 0;
    players_vector[index].item.movable.y = 0;
    players_vector->count++;
}

int player_mgr_get_player_index(player_vector_t *players_vector, uint32_t id)
{
    int index;
    for (int i = 0; i < players_vector->count; i++)
    {
        if (players_vector[i].item.id == id)
            return index = i;
    }
    return -1;
}

void player_mgr_set_player_transform(player_vector_t *players_vector, uint32_t id, float player_x, float player_y)
{
    int index = player_mgr_get_player_index(players_vector, id);
    if (index == -1) return;
    players_vector[index].item.movable.x = player_x;
    players_vector[index].item.movable.y = player_y;
}

void player_mgr_find_player(player_vector_t *players_vector, char *msg_content)
{
    if (players_vector->count >= 3) return; // handle only 4 players

    if(msg_content)
    {
        bomberman_t temp_player;
        int id;
        float x, y;
        memcpy(&id, &msg_content[0], sizeof(int));
        //memcpy(&x, &msg_content[4], sizeof(float));
        //memcpy(&y, &msg_content[8], sizeof(float));
        temp_player.id = id;

        /* add new player to the list */
        if(player_mgr_get_player_index(players_vector, id) == -1)
        {
            player_mgr_add_player(players_vector, id);
            //player_mgr_set_player_transform(players_vector, id, x, y);
        }
        else
        {
            return;
        }
    }
}

void player_mgr_update_transform(player_vector_t *players_vector, char *msg_content)
{
    int id;
    float x, y;
    memcpy(&id, &msg_content[0], sizeof(int));
    memcpy(&x, &msg_content[4], sizeof(float));
    memcpy(&y, &msg_content[8], sizeof(float));

    player_mgr_set_player_transform(players_vector, id, x, y);
}