#pragma once
struct game_krno_sost{
	int a[3][3];
	int l;
};
struct game_krno_xod{
	int x;
	int y;
};
struct game* krno_create_game();
void krno_delete_game(struct game* list);
void* krno_create_move();
