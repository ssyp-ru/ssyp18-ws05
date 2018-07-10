#include "players_kings.h"
#include "game_kings.h"
#include "engine.h"

#include <stdio.h>
#include <stdlib.h>

static void* create_pl_state() {
	struct pl_kings_state* random = (struct pl_kings_state*)malloc(sizeof(struct pl_kings_state));
	random->m = (struct game_kings_move*)malloc(sizeof(struct game_kings_move));
	return random;

}

static void delete_pl_state(void* pl_kings_state) {
	struct pl_kings_state* r_s = (struct pl_kings_state*) pl_kings_state;

	free(r_s->m);
	free(pl_kings_state);
}

static void* pl_random_decide_move(struct player* pl, struct game* game_state) {

	struct pl_kings_state* pl_random_state = (struct pl_kings_state*) pl->players;
    int count = 0;
	void** moves = game_state->_get_moves(game_state, &count);
    struct game_kings_move** king_moves = (struct game_kings_move**)moves;
	int rand1 = rand() % count;

	pl_random_state->m->x = king_moves[rand1]->x;
    pl_random_state->m->y = king_moves[rand1]->y;

    for(int i = 0; i < count; i++) {
        free(moves[i]);
    }
    free(moves);

    return pl_random_state->m;
}

static void* pl_kibord_decide_move(struct player* pl, struct game* game_state) {

	struct pl_kings_state* pl_kibord_state  = (struct pl_kings_state*) pl->players;

	int i = 0, j = 0;

	pl_kibord_state->m->x = -1;
	pl_kibord_state->m->y = -1;

	void* move2 = (void*)pl_kibord_state->m;

	do {

		scanf("%d %d", &i, &j);

		pl_kibord_state->m->x = i;
		pl_kibord_state->m->y = j;


	} while (game_state->_is_possible(game_state, move2) == 0);

	return move2;
}

static void* choose(struct player* pl, struct game* board);

static int who_wins(struct game* board) {
    printf("entered whowins\n");
	struct game_kings_state* board1 = (struct game_kings_state*) board->area;
	int player = board1->player;
	int player1 = 1 - player;

	if (board->_is_game_over(board) == 1) {
        printf("entered if\n");
        int winner = board->_get_vinner(board);
		return winner;
	}
	else {
        printf("entered else\n");
		int length = 0;
		void** ret = board->_get_moves(board, &length);
        printf("length: %d\n", length );

		for (int i = 0; i < length; i++) {
			struct game* board2 = board->_clone_area(board);
			board2->_do_move(board2, ret[i]);

			if (who_wins(board2) == player) {
				for (int i = 0; i < length; i++) {
					free(ret[i]);
				}
				free(ret);
				kings_delete_game(board2);
				return board1->player;
			}
			else {
				kings_delete_game(board2);
			}

		}


		for (int i = 0; i < length; i++) {
			free(ret[i]);
		}
		free(ret);
		return player1;
	}
}

static void* choose(struct player* pl, struct game* board)
{
	struct game_kings_state* board_state = (struct game_kings_state*) board->area;
	struct  pl_kings_state* pl_state = (struct pl_kings_state*)pl->players;
	struct game_kings_move* move = (struct game_kings_move*)malloc(sizeof(struct game_kings_move));
	void* move1 = (void*)move;

	int length = 0;
	int count = 0;
	void** ret = board->_get_moves(board, &length);
	printf("length: %d\n", length );
	struct game_kings_move** ret1 = (struct game_kings_move**) ret;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			move->x = i;
			move->y = j;

			if (board->_is_possible(board, move1) == 0) {
				count++;
			}
		}
	}
	count = 64 - count;
	if (count<=20){
		printf("calculating!\n");
		for (int i = 0; i < length; i++) {
			struct game* board2 = board->_clone_area(board);
			board2->_do_move(board2, ret[i]);
			if (who_wins(board2) == board_state->player){
				printf("i win!\n");
				kings_delete_game(board2);
				pl_state->m->x = ret1[i]->x;
				pl_state->m->y = ret1[i]->y;

				for (int i = 0; i < length; i++) {
					free(ret[i]);
				}
				free(ret);
				free(move);
				count = 0;
				return pl_state->m;

			}
			printf("endless night 2\n");
			kings_delete_game(board2);
		}
		printf("i lose!\n");
		for (int i = 0; i < length; i++) {
			free(ret[i]);
		}
		free(ret);
		free(move);
		return pl_random_decide_move(pl, board);

	}
	else {

		count = 0;
		for (int i = 0; i < length; i++) {
			free(ret[i]);
		}
		free(ret);
		free(move);
		return pl_random_decide_move(pl, board);
	}
}

struct player* kings_create_keyboard_player()
{
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->_delete_player_st = delete_pl_state;
    list->_decide_move = pl_kibord_decide_move;
    list->players = create_pl_state();
    return list;
}

struct player* kings_create_random_player()
{
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->_delete_player_st = delete_pl_state;
    list->_decide_move = pl_random_decide_move;
    list->players = create_pl_state();
    return list;

}
struct player* kings_create_choosebot_player()
{
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->_delete_player_st = delete_pl_state;
    list->_decide_move = choose;
    list->players = create_pl_state();
    return list;
}

void kings_delete_player(struct player* player)
{
    player->_delete_player_st(player->players);
    free(player);
}
