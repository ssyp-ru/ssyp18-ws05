#include<stdio.h>
#include<stdlib.h>
#include "game_kn15_15.h"
#include "player_kn15_15.h"
#include "neuron_net.h"
#include "agent_.h"
static void* create_pl(){
	struct  player_state15*  list = (struct player_state15*) malloc(sizeof (struct player_state15));
	struct  game_xod15*  lis = (struct game_xod15*) malloc(sizeof(int)*2);
	list->m=lis;
	return (void*) list;
}
static void delete_pl (void* pl_state){
	free(((struct player_state15*)pl_state)->m);
	free(pl_state);
}
static void* pl_2_decide(struct player* pl_state,struct game* dor){
	do{
		(*((struct player_state15*)(pl_state->players))->m).x = rand()%BRAIN;
		(*((struct player_state15*)(pl_state->players))->m).y = rand()%BRAIN;
	}
	while(dor->_is_possible(dor,((struct player_state15*)(pl_state->players))->m )!=1 );

	return ((struct player_state15*)(pl_state->players))->m;
}
static void* pl_1_decide(struct player* pl_state, struct game*dor){
	do{
		scanf("%d%d",&(*( (struct player_state15*)(pl_state->players) )->m).x, &(*( (struct player_state15*)(pl_state->players) )->m).y) ;
		if(dor->_is_possible(dor,((struct player_state15*)(pl_state->players))->m)  != 0){
			return ((struct player_state15*)(pl_state->players))->m;
		}
		printf("@$1&#*@$!&@\n");
	}while(1>0);
}
struct player* kn_15_15_create_player(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    //list->_create_player_st = create_pl;
    list->inform_resultfunc = NULL;
    list->_delete_player_st = delete_pl;
    list->_decide_move = pl_1_decide;
    list->players = create_pl();
    return list;
}
void kn_15_15_delete_player(struct player* player){
    player->_delete_player_st(player->players);
    free(player);
}
struct player* kn_15_15_create_player_random(){
    struct player* list = (struct player*) malloc(sizeof(struct player));
    //list->_create_player_st = create_pl;
    list->_delete_player_st = delete_pl;
    list->inform_resultfunc = NULL;
    list->_decide_move = pl_2_decide;
    list->players = create_pl();
    return list;
}

static double nn_place_values(struct game *game, void *nn_void)
{
    struct neural_network* nn = (struct neural_network*)nn_void;
    struct game_sost15* a = (struct game_sost15*)game->area;
    for (int i=0;i<BRAIN;i++)
    {
        for (int j=0;j<BRAIN;j++)
        {
            nn->layers[0]->neurons[(i*BRAIN+j)*3]->value=0;
            nn->layers[0]->neurons[(i*BRAIN+j)*3+1]->value=0;
            nn->layers[0]->neurons[(i*BRAIN+j)*3+2]->value=0;
            if (a->a[i][j] == a->l - 1)
                nn->layers[0]->neurons[(i*BRAIN+j)*3+1]->value=1;
            else if (a->a[i][j]>0)
                nn->layers[0]->neurons[(i*BRAIN+j)*3+2]->value=1;
            else
                nn->layers[0]->neurons[(i*BRAIN+j)*3]->value=1;
        }
    }
    calculate(nn);
    return nn->layers[nn->number_layers+1]->neurons[0]->value;
}

static void nn_update_values(struct game* game,struct game* game1, void *nn_void)
{
    struct neural_network* nn = (struct neural_network*)nn_void;
    double *val = (double *) malloc(sizeof(double));
    val[0]=nn_place_values(game1,nn);
    nn_place_values(game, nn);
    n_last_delta(nn, val);
    n_delta(nn, 100000);

    free(val);
}

static void nn_inform_result_agent(struct player* pl,int result)
{
    struct pl_st_agent* player_state = (struct pl_st_agent*)(pl->players);
    struct game* game_s = (struct game*)(player_state->area);

    double *val = (double *) malloc(sizeof(double));
    val[0]=result;
    nn_place_values(game_s, player_state->data);
    n_last_delta(player_state->data, val);
    n_delta(player_state->data, 10000);

    free(val);
}

static void* kn15_nn_createdata(char* filename)
{
    FILE *f = fopen(filename,"r");
    if (f==NULL)
    {
        return create_n_network(BRAIN*BRAIN*3,1,NN_HIDDEN_LAYERS_SIZE,NN_HIDDEN_LAYERS_COUNT);
    }
    else
    {
        return file_read(filename);
    }
}

static void kn15_nn_savedata(void* data,const char* file)
{
    file_print((struct neural_network*)data, file);
}

struct player* kn15_create_player_agent()
{
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->inform_resultfunc = nn_inform_result_agent;
    list->_delete_player_st = delete_pl_st_agent;
    list->_decide_move = decide_move_agent;

    get_value_fp value = nn_place_values;
    update_value_fp update = nn_update_values;
    savedata save_data_ = kn15_nn_savedata;
    getdata get_data_ = kn15_nn_createdata;

    list->players = create_pl_st_agent(value,update,get_data_,save_data_, add_move_15());
    return list;
    //update_value_fp update = nn_update_values;
    //get_value_fp value = nn_place_values;
}

struct player* kn15_create_player_agent_2(struct player* player_)
{
    struct player* list = (struct player*) malloc(sizeof(struct player));
    list->inform_resultfunc = nn_inform_result_agent;
    list->_decide_move = decide_move_agent;
    list->_delete_player_st = delete_pl_st_agent;

    struct pl_st_agent* agent = (struct pl_st_agent*)(player_->players);
    struct pl_st_agent* a = (struct pl_st_agent*)malloc(sizeof(struct pl_st_agent));
    printf("hello3\n");
    a->data = agent->data;
    a->move = add_move_15();
    a->area = NULL;
    a->fist_second = 0;
    a->vas_random = 0;
    a->_save_data_= kn15_nn_savedata;
    a->get_value = nn_place_values;
    a->update_value = nn_update_values;
    list->players = a;
    return list;
}

