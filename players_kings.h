#pragma once

struct pl_kings_state {
	struct game_kings_move* m;
};

struct player* kings_create_keyboard_player();
struct player* kings_create_random_player();
struct player* kings_create_choosebot_player();
void kings_delete_player(struct player* player);
