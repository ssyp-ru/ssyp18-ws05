#include<stdio.h>
#include<stdlib.h>
#include "engine.h"
#include "game_kn15_15.h"

static void clone_move(void* move1,void* move2){
    ((struct game_xod15*)move2)->x = ((struct game_xod15*)move1)->x;
    ((struct game_xod15*)move2)->y = ((struct game_xod15*)move1)->y;
}
static void* creat_dor(){
	struct  game_sost15*  list = (struct game_sost15*) malloc(sizeof( struct game_sost15));
	for (int i=0; i<BRAIN ;i++){
		for(int j=0; j<BRAIN ;j++){
			list->a[i][j]=0;
		}
	}
	list->l=0;
	return (void*) list;
}
static void de_te (struct game* dor){
	free(dor->area);
}
static void make_xod (struct game* dor, void* move){
    struct game_sost15* area = (struct game_sost15*)(dor->area);
	area->a[((struct game_xod15*)move)->x][((struct game_xod15*)move)->y]=area->l + 1;

	if(((struct game_sost15*)(dor->area))->l == 1){
        ((struct game_sost15*)(dor->area))->l=0;
    }else if(((struct game_sost15*)(dor->area))->l == 0){
        ((struct game_sost15*)(dor->area))->l=1;
    }else{
        printf("ERROR!\n");
    }
 }
static int prov(struct game* dor, void* move){
    struct game_sost15* area = (struct game_sost15*)(dor->area);
	if ((((struct game_xod15*)move)->x<BRAIN)&&(((struct game_xod15*)move)->y <BRAIN)&&(((struct game_xod15*)move)->x >= 0)&&(((struct game_xod15*)move)->y >= 0)){
		if (area->a[((struct game_xod15*)move)->x][((struct game_xod15*)move)->y] == 0){
			return 1;
		}
	}
	return 0;
}

static int v_horizontal(struct game* dor, int y0, int x0)
{
    struct game_sost15* area = (struct game_sost15*)(dor->area);

    if(x0 + 4 > BRAIN - 1) return 2;

    int type = area->a[y0][x0];
    if(type == 0) return 2;

    for(int j = x0; j < x0 + 5; j++) {
            if(area->a[y0][j] != type) return 2;
    }

    return type - 1;
}

static int v_vertical(struct game* dor, int y0, int x0)
{
    struct game_sost15* area = (struct game_sost15*)(dor->area);

    if(y0 + 4 > BRAIN - 1) return 2;

    int type = area->a[y0][x0];
    if(type == 0) return 2;

    for(int j = y0; j < y0 + 5; j++) {
            if(area->a[j][x0] != type) return 2;
    }

    return type - 1;
}

static int v_diagonal1(struct game* dor, int y0, int x0)
{
    struct game_sost15* area = (struct game_sost15*)(dor->area);

    if(x0 + 4 > BRAIN - 1) return 2;
    if(y0 + 4 > BRAIN - 1) return 2;

    int type = area->a[y0][x0];
    if(type == 0) return 2;

    for(int i = 0; i < 5; i++) {
            if(area->a[y0 + i][x0 + i] != type) return 2;
    }

    return type - 1;
}

static int v_diagonal2(struct game* dor, int y0, int x0)
{
    struct game_sost15* area = (struct game_sost15*)(dor->area);

    if(x0 - 4 < 0) return 2;
    if(y0 + 4 > BRAIN - 1) return 2;

    int type = area->a[y0][x0];
    if(type == 0) return 2;

    for(int i = 0; i < 5; i++) {
            if(area->a[y0 + i][x0 - i] != type) return 2;
    }

    return type - 1;
}


static int victori(struct game* dor){
    struct game_sost15* area = (struct game_sost15*)(dor->area);

	for(int i = 0; i < BRAIN; i++) {
        for(int j = 0; j < BRAIN; j++) {
            int v = v_horizontal(dor, i, j);
            if(v != 2) return v;
            v = v_vertical(dor, i, j);
            if(v != 2) return v;
            v = v_diagonal1(dor, i, j);
            if(v != 2) return v;
            v= v_diagonal2(dor, i, j);
            if(v != 2) return v;
        }
	}

	int g = 0;
    for(int i=0;i<BRAIN;i++){
        for (int j=0;j<BRAIN;j++){
            if (area->a[i][j]!=0){
                g=g+1;
            }
        }
    }
    if(g==BRAIN*BRAIN){
        return 2;
    }
    return 3;
}

static int game_over(struct game* dor)
{
	int g = victori(dor);
	if(g < 3) return 1;
	return 0;

}

static void write(struct game* dor){
	for (int i=0;i<BRAIN;i++){
		for(int j=0;j<BRAIN;j++){
			printf("%d ",((struct game_sost15*) (dor->area))->a[i][j]);
		}
		printf("\n");
	}
}

static struct game*clone(struct game* dor){
	struct game* g = kn15_15_create_game();
	for (int i=0;i<BRAIN;i++){
		for(int j=0;j<BRAIN;j++){
			((struct game_sost15*)(g->area))->a[i][j]=((struct game_sost15*)(dor->area))->a[i][j];
		}
	}
	((struct game_sost15*)(g->area))->l=((struct game_sost15*)(dor->area))->l;
	return g;
}
static void**get_possibb_move(struct game*dor, int*length){
	void** vozrat=(void**)malloc(sizeof(void*)*BRAIN*BRAIN);
	int r=0;
	for(int i=0;i<BRAIN;i++){
		for(int j=0;j<BRAIN;j++){
			if (((struct game_sost15*)(dor->area))->a[i][j]==0){
                 vozrat[r]=(struct game_xod15*)malloc(sizeof(struct game_xod15));
				((struct game_xod15*)vozrat[r])->x=i;
				((struct game_xod15*)vozrat[r])->y=j;
				r=r+1;
			}
		}
	}
	*length=r;
	return vozrat;
}
void* add_move_15(){
    struct game_xod15* move= (struct game_xod15*) malloc(sizeof(struct game_xod15));
    move->x=0;
    move->y=0;
    return move;
}

struct game* kn15_15_create_game(){
    struct game* list = (struct game*) malloc(sizeof(struct game));
    list->_create_game_area = creat_dor;
    list->_delete_game_area = de_te;
    list->_is_possible = prov;
    list->_get_vinner = victori;
    list->_is_game_over = game_over;
    list->_do_move = make_xod;
    list->_print_this = write;
    list->_clone_area = clone;
    list->_get_moves = get_possibb_move;
    list->_clone_move = clone_move;
    list->area= creat_dor();
    return list;
}
void kn15_15_delete_game(struct game* list){
    list->_delete_game_area(list->area);
    free(list);
}
