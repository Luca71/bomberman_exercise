#define CLOVE_SUITE_NAME player_mgr_test
#include "clove-experimental.h"
#include "player_mgr.h"

player_vector_t *players;

CLOVE_SUITE_SETUP() {
    players = player_mgr_new_vector();
}
CLOVE_SUITE_TEARDOWN() {
    player_mgr_list_free(players);
}
CLOVE_TEST(PlayerMgrNewTest)                    
{
    CLOVE_NOT_NULL(players);
}
CLOVE_TEST(PlayerMgrAdd)
{
    int id = 100;
    player_mgr_add_player(players, id);
    CLOVE_INT_EQ(id, players[0].item.id);
    CLOVE_INT_EQ(1, players->count);
}
CLOVE_TEST(PlayerMgrCounterIncrement)
{
    int id = 100;
    player_mgr_add_player(players, id);
    CLOVE_INT_EQ(1, players->count);
}
CLOVE_TEST(PlayerMgrSetPlayertransform)
{
    int id = 100;
    player_mgr_add_player(players, id);
    player_mgr_set_player_transform(players, 100, 15, 20);
    CLOVE_FLOAT_EQ(15, players[0].item.movable.x);
    CLOVE_FLOAT_EQ(20, players[0].item.movable.y);
}


