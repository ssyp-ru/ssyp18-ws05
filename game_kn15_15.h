#pragma once
#include "engine.h"
#define BRAIN 10
struct game_sost15{
	int a[BRAIN][BRAIN];
	int l;
};
struct game_xod15{
	int x;
	int y;
};
struct game* kn15_15_create_game();
void kn15_15_delete_game(struct game* list);
void* add_move_15();
