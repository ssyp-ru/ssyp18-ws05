#include <stdlib.h>
#include <stdio.h>
#include "engine.h"
#include "player_lab.h"
#include "game_lab.h"

static void* create_player_state(){
	struct player_stats *_ps = (struct player_stats*) malloc(sizeof(struct player_stats));
	struct gmove* _move = (struct gmove*) malloc(sizeof(struct gmove));
	_move->x=0;
	_move->y=0;
	_ps->wayscore = 0;
	_ps->way = (int*)malloc(sizeof(int) * SIZE*SIZE);
	_ps->way[0] = -1;
	_ps->move = _move;
	return _ps;
}
static void delete_player_states(void* player_st){
	struct player_stats *_player_st = (struct player_stats*)player_st;
	free(_player_st->move);
	free(player_st);
}
static void* decide_move_ai(struct player* player_st, struct game* garea){
	int delscore = 0, stonescore = 0;
	struct game_area* _area = (struct game_area*)garea;
	struct player_stats* _ps = (struct player_stats*)(player_st->players);
	int numways = 4;
	struct game* __area = garea->_clone_area(garea);
	struct game_area *custom_area = __area->area;
	int del_moves[SIZE*SIZE][2];
	int	stone[SIZE*SIZE][2];
	bool isdel = true;
	int score = 10,csx=_area->ccords[1][0],csy=_area->ccords[1][1];
	int prex, prey;
	if (_ps->way[0]==-1)
	while (__area->_is_game_over(__area) == 0)
	{
		struct gmove** qmoves = (struct gmove**)garea->_get_moves(__area, &numways);
		for (int i = 0; i < numways; i++)
		{
			isdel = true;
			for (int j = 0; j < delscore; j ++)
				if ((qmoves[i]->x == del_moves[j][0]) && (qmoves[i]->y == del_moves[j][1]))
					isdel = false;
			if ((isdel) && (garea->_is_possible(__area, qmoves[i]) == 1))
			{
				if (numways > 2)
				{
					stone[stonescore][0] = csx;
					stone[stonescore][1] = csy;
					stonescore++;
				}
				csx = qmoves[i]->x;
				csy = qmoves[i]->y;
				del_moves[delscore][0] = csx;
				del_moves[delscore][1] = csy;
				delscore++;
				_ps->way[score * 2-20] = csx;
				_ps->way[score * 2-19] = csy;
				custom_area->ccords[custom_area->obj][0] = csx;
				custom_area->ccords[custom_area->obj][1] = csy;
				custom_area->area[csy][csx] = score;
				score++;
				break;
			}
			else
			{
				if (i == numways - 1)
				{
					stonescore --;
					csx = stone[stonescore][0];
					csy = stone[stonescore][1];
					while (score != custom_area->area[csy][csx])
					{
						_ps->way[score * 2 - 20] = 0;
						_ps->way[score * 2 - 19] = 0;
						score--;
					}
					custom_area->ccords[custom_area->obj][0] = csx;
					custom_area->ccords[custom_area->obj][1] = csy;
					custom_area->area[csy][csx] = score;
					score++;
				}
			}
		}
		for (int i=0;i<numways;i++)
			free(qmoves[i]);
		free(qmoves);
	}
	_ps->move->x = _ps->way[_ps->wayscore];
	_ps->move->y = _ps->way[_ps->wayscore+1];
	_ps->wayscore += 2;
	free(custom_area);
	free(__area);
	return _ps->move;
}
static void* decide_move_pl(struct player* player_st, struct game* area){
	struct game_area* _area = (struct game_area*)(area->area);
	struct player_stats* _ps = (struct player_stats*)(player_st->players);
	int xm = _area->ccords[_area->obj][0];
	int ym = _area->ccords[_area->obj][1];

	_ps->move->x = xm;
	_ps->move->y = ym;

	char cmove=getchar();
	while (cmove == '\n')
	{
		cmove = getchar();
	}
		switch (cmove)
		{
		case 'w':
			_ps->move->x = xm;
			_ps->move->y = ym - 1;
			break;
		case 's':
			_ps->move->x = xm;
			_ps->move->y = ym + 1;
			break;
		case 'a':
			_ps->move->x = xm - 1;
			_ps->move->y = ym;
			break;
		case 'd':
			_ps->move->x = xm + 1;
			_ps->move->y = ym;
			break;
		}
	if (area->_is_possible(area, _ps->move) == 0)
		_ps->move = (struct gmove*) decide_move_pl(player_st, area);
	return _ps->move;
}
struct player* lab_create_player(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->inform_resultfunc = NULL;
    list->_delete_player_st = delete_player_states;
    list->_decide_move = decide_move_pl;
    list->players = create_player_state();
    return list;
}
void lab_delete_player(struct player* player){
    player->_delete_player_st(player->players);
    free(player);
}
struct player* lab_create_player2(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->inform_resultfunc = NULL;
    list->_delete_player_st = delete_player_states;
    list->_decide_move = decide_move_ai;
    list->players = create_player_state();
    return list;
}
