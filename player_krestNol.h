#pragma once
#define ALPHA 0.5
#define D 0.1
#include "engine.h"
#include "math.h"
struct player_krno_state
{
	struct game_krno_xod* m;
};

struct player* krno_create_player();
void krno_delete_player(struct player* player);
struct player* krno_create_player_random();
struct player* krno_creat_pl_agent();
