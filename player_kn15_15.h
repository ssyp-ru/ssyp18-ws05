#pragma once

#define NN_HIDDEN_LAYERS_COUNT 1
#define NN_HIDDEN_LAYERS_SIZE BRAIN*BRAIN*3

struct player_state15 {
	struct game_xod15* m;
};
struct player* kn_15_15_create_player();
struct player* kn_15_15_create_player_random();
struct player* kn15_create_player_agent();
struct player* kn15_create_player_agent_2(struct player* player_);
void kn_15_15_delete_player(struct player* player);
