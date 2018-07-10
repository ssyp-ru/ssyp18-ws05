#include <stdio.h>
#include <stdlib.h>
#include "agent_.h"
#include "engine.h"
#include "math.h"
#include "game_krestNol.h"
#include "player_krestNol.h"
#include "agent_.h"


static void* create_pl(){
	struct  player_krno_state*  list = (struct player_krno_state*) malloc(sizeof(struct player_krno_state));
	struct  game_krno_xod*  lis = (struct game_krno_xod*) malloc(sizeof(struct game_krno_xod));
	lis->x=0;
	lis->y=0;
	list->m=lis;
	return (void*) list;
}
static void delete_pl (void* pl_state){
    struct player_krno_state* state = (struct player_krno_state*)pl_state;
	free(state->m);
	free(pl_state);
}
static void* pl_2_decide(struct player* pl_state, struct game* dor){
    struct player_krno_state* state = (struct player_krno_state*)pl_state->players;
    int t=0;
    void** list = dor->_get_moves(dor,&t);
    int c=rand()%t;
    state->m->x = ((struct game_krno_xod*) list[c])->x;
    state->m->y = ((struct game_krno_xod*) list[c])->y;

    for (int i=0;i<t;i++){
        free(list[i]);
    }
    free(list);

    return state->m;
}
static void* pl_1_decide(struct player* pl_state, struct game* dor){
    struct player_krno_state* state = (struct player_krno_state*)pl_state->players;
    scanf("%d %d",&(state->m->x), &(state->m->y) );

    while(dor->_is_possible(dor,state->m) == 0){

        scanf("%d %d",&(state->m->x), &(state->m->y));
    }
	return ((struct player_krno_state*)(pl_state->players))->m;
}
static void* get_data(char*file){
    FILE* f=fopen(file,"r");
    int prow1= pow(3,9);
    double* data_d = (double*)malloc(sizeof(double)*prow1);
    void* data = (void*) data_d;
    if(f==NULL){
        //printf("COULD NOT OPEN FILE\n");
        for (int i=0; i<prow1;i++){
            data_d[i]=0.00;
        }
    }else{
        //printf("LOADING FILE\n");
        for (int i=0; i<prow1;i++){
            fscanf(f,"%lf",&(data_d[i]));
        }
    }
    fclose(f);
    return data;
}
static void save_data(void* data,const char* file){
    double* data_d = (double*)data;
    printf("save");
    FILE* f=fopen(file,"w");
    int prow1= pow(3,9);
    for (int i=0; i<prow1;i++){
        fprintf(f,"%lf ",data_d[i]);
        if(data_d[i] > 0.01) {
                //printf("success\n");
        }
    }
    fclose(f);
}
static double get_value(struct game* game,void* data){
    double* d = (double*) data;
    int t=0;
    struct game_krno_sost* a = (struct game_krno_sost*)game->area;
    int i=0;
    int j=0;
    for(int r=0;r<9;r++){
        i= r/3;
        j= r%3;
        t= t + (a->a[i][j]*pow(3,r));
    }
    double x = d[t];
    return x;
}
static void up_date(struct game* game_area, struct game* game1, void* data){
    struct game_krno_sost* a = (struct game_krno_sost*)(game_area->area);
    int t=0,i=0,j=0;
    for(int r=0;r<9;r++){
        i= r/3;
        j= r%3;
        t= t + (a->a[i][j]*pow(3,r));
    }
    struct game_krno_sost* a1 = (struct game_krno_sost*)(game1->area);
    int t1=0;
    i=0;
    j=0;
    for(int r=0;r<9;r++){
        i= r/3;
        j= r%3;
        t1= t1 + (a1->a[i][j]*pow(3,r));
    }
    int R = game_area->_is_game_over(game1);
    double val=get_value(game_area,data);
    if((((double*)data)[t1]< -0.00000001)||(((double*)data)[t1]> 0.00000001)){
        printf("v(s'): %lf\n",((double*)data)[t1]);
        printf("old v(s): %lf\n",((double*)data)[t]);

        ((double*)data)[t]=(((ALPHA * get_value(game1, data))-val)*D)+val;

        printf("new v(s): %lf\n",((double*)data)[t]);
    }else{
        ((double*)data)[t]=(((ALPHA * get_value(game1, data))-val)*D)+val;
    }
    if(R!=0){
        printf("%lf\n",((double*)data)[t]);
    }
}
static void inform_result_agent(struct player* player_st,int  result){
    struct game* game_s = (struct game*)(((struct pl_st_agent*)(player_st->players))->area);
    struct game_krno_sost* a = (struct game_krno_sost*)(game_s->area);
    void* data = ((struct pl_st_agent*)(player_st->players))->data;
    int t=0,i=0,j=0;
    for(int r=0;r<9;r++){
        i= r/3;
        j= r%3;
        t= t + (a->a[i][j]*pow(3,r));
    }
    int R = result;
    double val=get_value(game_s,data);
    ((double*)data)[t]= (R-val)*D+val;
    printf("old v(s): %lf; new v(s): %lf\n",val, ((double*)data)[t]);
}

struct player* krno_create_player(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    //list->_create_player_st = create_pl;
    list->inform_resultfunc = NULL;
    list->_delete_player_st = delete_pl;
    list->_decide_move = pl_1_decide;
    list->players = create_pl();
    return list;
}
void krno_delete_player(struct player* player){
    player->_delete_player_st(player->players);
    free(player);
}
struct player* krno_create_player_random(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    //list->_create_player_st = create_pl;
    list->inform_resultfunc = NULL;
    list->_delete_player_st = delete_pl;
    list->_decide_move = pl_2_decide;
    list->players = create_pl();
    return list;
}
struct player* krno_creat_pl_agent(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    //list->_create_player_st = create_pl_st_agent;
    list->inform_resultfunc = inform_result_agent;
    list->_delete_player_st = delete_pl_st_agent;
    list->_decide_move = decide_move_agent;

    get_value_fp value = get_value;
    update_value_fp update = up_date;
    savedata save_data_ = save_data;
    getdata get_data_ = get_data;

    list->players = create_pl_st_agent(value,update,get_data_,save_data_, krno_create_move());
    return list;
}
struct player* krno_creat_pl_agent_2(struct player* player_){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->inform_resultfunc = inform_result_agent;
    list->_decide_move = decide_move_agent;
    list->_delete_player_st = delete_pl_st_agent;

    struct pl_st_agent* agent = (struct pl_st_agent*)(player_->players);
    struct pl_st_agent* a = (struct pl_st_agent*)malloc(sizeof(struct pl_st_agent));
    printf("hello3\n");
    a->data = agent->data;
    a->move = krno_create_move();
    a->area = NULL;
    a->fist_second = 0;
    a->vas_random = 0;
    a->_save_data_= save_data;
    a->get_value = get_value;
    a->update_value = up_date;
    list->players = a;
    return list;
}
