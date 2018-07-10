#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "game_krestNol.h"

static void clone_move(void* move1,void* move2){
    ((struct game_krno_xod*)move2)->x = ((struct game_krno_xod*)move1)->x;
    ((struct game_krno_xod*)move2)->y = ((struct game_krno_xod*)move1)->y;
}
static void* creat_dor(){
	struct  game_krno_sost*  list = (struct game_krno_sost*) malloc(sizeof(struct game_krno_sost));
	for (int i=0; i<3 ;i++){
		for(int j=0; j<3 ;j++){
			(*list).a[i][j]=0;
		}
	}
	(*list).l=0;
	return (void*) list;
}
static void de_te (struct game* dor){
    //void*a = ((struct game_krno_sost*)(dor->area))->a;
    //free(a);
	free(dor->area);
}
static void make_xod (struct game* dor, void* move){
    if(((struct game_krno_sost*)(dor->area))->l == 1){
        ((struct game_krno_sost*)(dor->area))->l=2;
    }else if(((struct game_krno_sost*)(dor->area))->l == 2){
        ((struct game_krno_sost*)(dor->area))->l=1;
    }else if(((struct game_krno_sost*)(dor->area))->l == 0){
        ((struct game_krno_sost*)(dor->area))->l=1;
    }
    ((struct game_krno_sost*)(dor->area))->a[((struct game_krno_xod*)move)->x][((struct game_krno_xod*)move)->y] = ((struct game_krno_sost*)(dor->area))->l;
}
static int prov(struct game* dor,void* move){

	if ((((struct game_krno_xod*)move)->x < 3)&&( ((struct game_krno_xod*)move)->y <3 )&&( ((struct game_krno_xod*)move)->x >= 0 )&&( ((struct game_krno_xod*)move)->y >= 0 )){
		if (((struct game_krno_sost*)(dor->area))->a[((struct game_krno_xod*)move)->x][((struct game_krno_xod*)move)->y] == 0){
			return 1;
		}
	}
	//printf("%d %d",((struct game_xod*)move)->x,((struct game_xod*)move)->y);
	printf("Make another move!!!");
	return 0;
}
static int get_winner(struct game* dor1){
    int j=0;
    struct game_krno_sost* dor = (struct game_krno_sost*)(((struct game*)dor1)->area);
	for (int y=0;y<3;y++)
	{
        if ((dor->a[y][j] == 1)&&(dor->a[y][j+1] == 1)&&(dor->a[y][j+2] == 1))
        {
            return 0;
        } else if ((dor->a[j][y] == 1)&&(dor->a[j+1][y] == 1)&&(dor->a[j+2][y] == 1))
        {
            return 0;
        }
    }
    int t=0;
    for (int i=0, j=0; (i<3)&&(j<3); i++,j++)
	{
        if (dor->a[i][j] == 1)
        {
            t++;
        }
    }
    if(t==3){
        return 0;
    }
    t=0;
    for (int i=0,j=2;(i<3)&&(j>=0);i++,j--)
	{
            if (dor->a[i][j] == 1)
            {
                t++;
            }
    }
    if(t==3){
        return 0;
    }

	for (int y=0;y<=2;y++)
		{
			if ((dor->a[y][j]==2)&&(dor->a[y][j+1]==2)&&(dor->a[y][j+2]==2))
			{
				return 1;
			} else if ((dor->a[j][y]==2)&&(dor->a[j+1][y]==2)&&(dor->a[j+2][y]==2))
			{
				return 1;
			}
		}
    t=0;
    for (int i=0, j=0; (i<3)&&(j<3); i++, j++)
	{
            if (dor->a[i][j] == 2)
            {
                t++;
            }
    }
    if(t==3){
        return 1;
    }
    t=0;
    for (int i=0,j=2;(i<3)&&(j>=0);i++,j--)
	{
            if (dor->a[i][j] == 2)
            {
                t++;
            }
    }
    if(t==3){
        return 1;
    }
    return 2;
}
static int is_gameover(struct game* dor){
    if(get_winner(dor)==2){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(((struct game_krno_sost*) (dor->area))->a[i][j] == 0){
                    return 0;
                }
            }
        }
        return 1;
    }else{
        return 1;
    }
}
static void write(struct game* dor){
	for (int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d ",((struct game_krno_sost*)(((struct game*)dor)->area))->a[i][j]);
		}
		printf("\n");
	}
}
static struct game* clone(struct game* dor){
    struct game* clon1 = krno_create_game();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ((struct game_krno_sost*)(clon1->area))->a[i][j] = ((struct game_krno_sost*)(dor->area))->a[i][j];
        }
    }
    //write(clon1);
    ((struct game_krno_sost*)(clon1->area))->l = ((struct game_krno_sost*)(dor->area))->l;
    return clon1;
}
static void** get_poss(struct game* dor,int* nXod){
    void** list = (void**) malloc(sizeof(void*)*9);
    int r=0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){

            if(r<9){
                if(((struct game_krno_sost*)(dor->area))->a[i][j] == 0){
                    list[r]=(struct game_krno_xod*) malloc(sizeof(struct game_krno_xod));
                   ((struct game_krno_xod*) list[r])->x = i;
                   ((struct game_krno_xod*) list[r])->y = j;
                   r++;
                }
            }
        }
    }

   *nXod = r;
   return list;
}
void* krno_create_move(){
    struct game_krno_xod* move= (struct game_krno_xod*) malloc(sizeof(struct game_krno_xod));
    move->x=0;
    move->y=0;
    return move;
}
struct game* krno_create_game(){
    struct game* list = (struct game*) malloc(sizeof(struct game));
    list->_create_game_area = creat_dor;
    list->_delete_game_area = de_te;
    list->_is_possible = prov;
    list->_get_vinner = get_winner;
    list->_is_game_over = is_gameover;
    list->_do_move = make_xod;
    list->_print_this = write;
    list->_clone_area = clone;
    list->_get_moves = get_poss;
    list->_clone_move = clone_move;
    list->area = creat_dor();
    //write(list);
    return list;
}

void krno_delete_game(struct game* list){
    list->_delete_game_area(list);
    //printf("delete area");
    free(list);
}
