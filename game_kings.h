#pragma once

struct game_kings_state {
	int A[8][8];
	int player;
};

struct game_kings_move {
	int x, y;
};

struct game* kings_create_game();
void kings_delete_game(struct game* list);
void* kings_create_move();
