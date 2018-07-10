#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "engine.h"
#define SIZE 40
struct gmove
{
	int x, y;
};
struct game_area
{
	int area[20][20], ccords[2][2], winx, winy, obj, size;
	bool win;
	struct gmove** prev1;
};

struct game* lab_create_game();
void lab_delete_game(struct game* list);
void* add_move_lab();
