#include "game_kings.h"
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
static void* create_board() {
	struct game_kings_state* board = (struct game_kings_state*)malloc(sizeof(struct game_kings_state));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board->A[i][j] = 0;
		}

	}

	board->player = 0;
	return board;
}

static struct game* clone(struct game* board)
{
    struct game *cloned = kings_create_game();

	struct game_kings_state* board2 = (struct game_kings_state*)cloned->area;
	struct game_kings_state* board1 = (struct game_kings_state*)board->area;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board2->A[i][j] = board1->A[i][j];
		}
	}
	board2->player = board1->player;

	return cloned;

}

static void destroy_board(struct game* board)
{
	free(board->area);
}

static void** get_possible_moves(struct game* board,int* length)
{
	struct game_kings_state* board1 = (struct game_kings_state*) board->area;

	int C[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			C[i][j] = 1;
		}
	}


	for (int k = 0; k < 8; k++) {
		for (int f = 0; f < 8; f++) {
			if (board1->A[k][f] == 1) {
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (((i + k) >= 0) && ((i + k)<8) && ((j + f) >= 0) && ((j + f)<8)) {
							C[i + k][j + f] = 0;
						}
					}
				}
			}
		}
	}

	struct game_kings_move** ret = (struct game_kings_move**)malloc(64*sizeof(struct game_kings_move*));

	int count = 0;

	for (int i=0;i<8;i++){
		for (int j = 0; j < 8; j++) {
			if (C[i][j] == 1) {
                ret[count] = (struct game_kings_move*)malloc(sizeof(struct game_kings_move));
				ret[count]->x = i;
				ret[count]->y = j;
				count++;
			}
		}
	}

	*length = count;
	void** ret1= (void**)ret;

	return ret1;

}

static int is_move_possibe(struct game* board, void* move)
{
	int summ = 0;

	struct game_kings_state* board1 = (struct game_kings_state*)board->area;
	struct game_kings_move* move1 = (struct game_kings_move*)move;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (((i + move1->x) >= 0) && ((i + move1->x)<8) && ((j + move1->y) >= 0) && ((j + move1->y)<8)) {
				summ += board1->A[i + move1->x][j + move1->y];
			}
		}
	}

	if (summ != 0) {
		return 0;
	}
	else {
		return 1;
	}


}

static void make_move(struct game* board, void* move) {

	struct game_kings_state* board1 = (struct game_kings_state*)board->area;

	struct game_kings_move* move1 = (struct game_kings_move*)move;

	if ((is_move_possibe(board, move) == 1) && (move1->x >= 0) && (move1->x <8) && (move1->y >= 0) && (move1->y < 8)){
		board1->A[move1->x][move1->y] = 1;
		board1->player = 1 - board1->player;
	}


}

static int is_gameover(struct game* board)
{
	int summ = 0, C[8][8];


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			C[i][j] = 0;
		}
	}

	struct game_kings_state* board1 = (struct game_kings_state*)board->area;

	for (int k = 0; k < 8; k++) {
		for (int f = 0; f < 8; f++) {
			if (board1->A[k][f] == 1) {
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (((i + k) >= 0) && ((i + k)<8) && ((j + f) >= 0) && ((j + f)<8)) {
							C[i + k][j + f] = 1;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			summ += C[i][j];
		}
	}

	if (summ == 64) {
		return 1;
	}
	return 0;

}

static int get_winner(struct game* board) {

	struct game_kings_state* board1 = (struct game_kings_state*)board->area;
	int summ = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			summ += board1->A[i][j];
		}
	}
	if (summ % 2 == 0) {
		 return 1;
	}
	else {
		 return 0;
	}

}

static void print(struct game* board)
{
	struct game_kings_move* cords = (struct game_kings_move*)malloc(sizeof(struct game_kings_move));
	void* cords1 = (void*)cords;

	struct game_kings_state* board1 = (struct game_kings_state*)board->area;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cords->x = i;
			cords->y = j;

			if ((is_move_possibe(board,cords1)==0)&&(board1->A[i][j]!=1)) {
				printf("* ");
			}
			else {
				printf("%d ", board1->A[i][j]);
			}

		}
		printf("\n");
	}
	printf("\n");

	free(cords1);
}

static void clone_move(void* move1,void* move2)
{
    ((struct game_kings_move*)move2)->x = ((struct game_kings_move*)move1)->x;
    ((struct game_kings_move*)move2)->y = ((struct game_kings_move*)move1)->y;
}

struct game* kings_create_game()
{
    struct game* list = (struct game*) malloc(sizeof(struct game));
    list->_create_game_area = create_board;
    list->_delete_game_area = destroy_board;
    list->_is_possible = is_move_possibe;
    list->_get_vinner = get_winner;
    list->_is_game_over = is_gameover;
    list->_do_move = make_move;
    list->_print_this = print;
    list->_clone_area = clone;
    list->_get_moves = get_possible_moves;
    list->_clone_move = clone_move;
    list->area = create_board();
    //write(list);
    return list;
};

void kings_delete_game(struct game* list)
{
    list->_delete_game_area(list->area);
    free(list);
}

void* kings_create_move()
{
    struct game_kings_move *m = (struct game_kings_move *)malloc(sizeof(struct game_kings_move));
    m->x = 0;
    m->y = 0;
    return m;
}
