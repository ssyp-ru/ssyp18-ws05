#pragma once
#include "engine.h"

struct player_stats
{
	struct gmove* move;
	int *way,wayscore;
};
struct player* lab_create_player();
struct player* lab_create_player2();
void lab_delete_player(struct player* player);
//struct player* lab_creat_pl_agent();
