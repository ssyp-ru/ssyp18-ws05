#include "game_lab.h"
#include "engine.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
static void clone_move(void* move1,void* move2)
{
    ((struct gmove*)move2)->x = ((struct gmove*)move1)->x;
    ((struct gmove*)move2)->y = ((struct gmove*)move1)->y;
}
static void print_area(struct game* area1)
{
	struct game_area *area = (struct game_area*) (((struct game*)area1)->area);
	int size = area->size;
	//system("cls");
	printf("Current sw - %d\n", area->obj + 1);
	printf("1(]): x - %d, y - %d\n", area->ccords[0][0], area->ccords[0][1]);
	printf("2([): x - %d, y - %d\n", area->ccords[1][0], area->ccords[1][1]);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			switch (area->area[i][j])
			{
			case 3:
				printf("F");
				break;
			case 2:
				printf("]");
				break;
			case 1:
				printf("0");
				break;
			case 4:
				printf("[");
				break;
			case 6:
				printf("O");
				break;
			default:
				printf(".");
				break;
			}
		}
		printf("\n");
	}
}
static void* create_area()
{
	int size = 20;
	struct game_area* a = (struct game_area*) malloc(sizeof(struct game_area));
	struct gmove** c = (struct gmove**) malloc(2 * sizeof(struct gmove*));
	c[0] = (struct gmove*) malloc(sizeof(struct gmove));
	c[1] = (struct gmove*) malloc(sizeof(struct gmove));
	a->prev1 = c;
	FILE *f = fopen("test.lb", "r");
	int b;
	a->win = false;
	a->size = size;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fscanf(f, "%d", &b);
			if ((b == 2)||(b==4))
			{
				a->ccords[b/2-1][0] = j;
				a->ccords[b/2-1][1] = i;
			}
			a->area[i][j] = b;
			if (b == 3)
			{
				a->winx = j;
				a->winy = i;
			}
		}
	}
	a->obj = 0;
	fclose(f);
	return a;
}
static void delete_area(struct game* area)	//не на каждый malloc есть free
{

	free(area->area);
}
static int qpossible(struct game* area, void *move)
{
	struct game_area* _area = (struct game_area*) (area->area);
	struct gmove *_move = (struct gmove *)move;
	int res = 1;
	if (
		(_area->area[_move->y][_move->x] == 1)||
		(
		(_move->y==_area->ccords[_area->obj][1])&&
		(_area->ccords[_area->obj][0]==_move->x)
		)
		)
		res = 0;
	return res;
}
static int qgame_over(struct game* area)
{
	struct game_area *_area = (struct game_area*) (((struct game*)area)->area);
	int vict = 0;
	if (_area->area[_area->winy][_area->winx] != 3)
	{
		vict = 1;
		_area->win = true;
	}
	return vict;
}
static int get_vinner(struct game* area)
{
	struct game_area *_area = (struct game_area*) (((struct game*)area)->area);
	return _area->obj;
}
static void do_move(struct game* area, void *move)
{
	struct game_area *_area = (struct game_area*) (((struct game*)area)->area);
	int cobj = _area->obj;
	struct gmove *_move = (struct gmove *)move;
	if (qpossible(area, _move)==1)
	{
		_area->prev1[cobj]->x = _area->ccords[cobj][0];
		_area->prev1[cobj]->y = _area->ccords[cobj][1];
		_area->area[_move->y][_move->x] += (cobj + 1) * 2;
		_area->area[_area->ccords[cobj][1]][_area->ccords[cobj][0]] -= (cobj + 1) * 2;
		_area->ccords[cobj][1] = _move->y;
		_area->ccords[cobj][0] = _move->x;
	}
	if (qgame_over(area) == 0)
	{
		if (_area->obj == 0)
			_area->obj++;
		else
			_area->obj--;
	}
	else
	{
		printf("The Winner is player No %d! Congrat!",get_vinner(area));
		getchar(); getchar();
	}
	print_area(area);
}
static struct game* clone_area(struct game* area)
{
	struct game* a = lab_create_game();
	struct game_area* _area = (struct game_area*) (area->area);
	for (int i = 0; i < _area->size; i++)
		for (int j = 0; j < _area->size; j++)
			((struct game_area*) a->area)->area[i][j] = _area->area[i][j];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			((struct game_area*) a->area)->ccords[i][j] = _area->ccords[i][j];
	((struct game_area*) a->area)->obj = _area->obj;
	((struct game_area*) a->area)->size = _area->size;
	((struct game_area*) a->area)->win = _area->win;
	((struct game_area*) a->area)->winx = _area->winx;
	((struct game_area*) a->area)->winy = _area->winy;
	((struct game_area*) a->area)->prev1 = (struct gmove**) malloc(2*sizeof(struct gmove*));
	((struct game_area*) a->area)->prev1[0] = _area->prev1[0];
	((struct game_area*) a->area)->prev1[1] = _area->prev1[1];
	return a;
}
static void** get_possible_moves(struct game* area, int* lenght)
{
	struct game_area *_area = (struct game_area*) (((struct game*)area)->area);
	struct gmove** a = (struct gmove**)malloc(4*sizeof(struct gmove*));
	for (int i = 0; i < 4; i++)
	{
	    struct gmove* c = (struct gmove*)malloc(sizeof(struct gmove));
		c->x = -1;
		c->y = -1;
		a[i] = c;
	}
	struct gmove* test = (struct gmove*)malloc(sizeof(struct gmove));
	int sx = _area->ccords[_area->obj][0], sy = _area->ccords[_area->obj][1];
	test->x = sx;
	test->y = sy - 1;
	if (qpossible(area, test) == 1)
	{
		a[0]->y = test->y;
		a[0]->x = test->x;
	}
	test->x = sx;
	test->y = sy + 1;
	if (qpossible(area, test) == 1)
	{
		a[1]->y = test->y;
		a[1]->x = test->x;
	}
	test->x = sx - 1;
	test->y = sy;
	if (qpossible(area, test) == 1)
	{
		a[2]->y = test->y;
		a[2]->x = test->x;
	}
	test->x = sx + 1;
	test->y = sy;
	if (qpossible(area, test) == 1)
	{
		a[3]->y = test->y;
		a[3]->x = test->x;
	}
	free(test);
	return (void**)a;
}
/*static void undo(struct game* area)
{
	struct game_area *_area = (struct game_area*) (((struct game*)area)->area);
	for (int i = 0; i < 2; i++)
	{
		do_move(area, _area->prev1[_area->obj]);
	}
}*/
void* add_move_lab()
{
    struct gmove* move= (struct gmove*) malloc(sizeof(struct gmove));
    move->x=0;
    move->y=0;
    return move;
}
struct game* lab_create_game()
{
    struct game* list = (struct game*) malloc(sizeof(struct game));
    list->_create_game_area = create_area;
    list->_delete_game_area = delete_area;
    list->_is_possible = qpossible;
    list->_get_vinner = get_vinner;
    list->_is_game_over = qgame_over;
    list->_do_move = do_move;
    list->_print_this = print_area;
    list->_clone_area = clone_area;
    list->_get_moves = get_possible_moves;
    list->_clone_move = clone_move;
    list->area= create_area();
    return list;
}
void lab_delete_game(struct game* list)
{
    list->_delete_game_area(list->area);
    free(list);
}
