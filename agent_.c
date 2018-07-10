#include "agent_.h"
#include <stdio.h>
#include <stdlib.h>

struct pl_st_agent* create_pl_st_agent(get_value_fp value, update_value_fp update,getdata get_data,savedata save_data,void* move){
    struct pl_st_agent *a = (struct pl_st_agent*)malloc(sizeof(struct pl_st_agent));
    printf("hello3\n");
    a->data = get_data("data.txt");
    a->move = move;
    a->area = NULL;
    a->fist_second = 1;
    a->vas_random = 0;
    a->_save_data_= save_data;
    a->get_value = value;
    a->update_value = update;
    return a;
}
void delete_pl_st_agent(void* agent){
    struct pl_st_agent* agent1 = ((struct pl_st_agent*)agent);
    if(agent1->fist_second == 1){
        agent1->_save_data_(agent1->data,"data.txt");
    }
    free(agent1->move);
    free(agent1->area);
    free(agent);
}
void* decide_move_agent(struct player* player,struct game* area)
{
    int x;
    struct pl_st_agent* pl = (struct pl_st_agent*)(player->players);
    struct game* s = pl->area;
    double c=rand()/(double)RAND_MAX;

    printf("CURRENT VALUE: %lf\n", pl->get_value(area, pl->data));

    void** get_pos = area->_get_moves(area, &x);
    struct game** clon=(struct game**) malloc(sizeof(struct game*)*x);

    for (int i=0; i<x; i++){
        clon[i] = area->_clone_area(area);
        area->_do_move(clon[i], get_pos[i]);
    }
    if((s!= NULL)&&( pl->vas_random == 0 )){
        pl->update_value(s,area,pl->data);
    }
    int max=0;




    if(c > E){
        printf("Greedy!\n");
        pl->vas_random = 0;
        double* value = (double*) malloc(sizeof(double)*x);
        max = 0;
        for (int i=0; i<x; i++){
            value[i]=pl->get_value(clon[i],pl->data);
            //printf("value[%d]: %f\n", i, value[i]);
        }
        for (int i=0; i<x; i++){
            if(value[i]<value[max]){
                max=i;
            }
        }
        //printf("%lf\n",value[max]);
        if(pl->area != NULL){
            pl->area->_delete_game_area(pl->area);
            free(pl->area);
        }
        pl->area = area->_clone_area(area);

        area->_clone_move(get_pos[max],pl->move);
        free(value);
    } else {
        printf("Exploring!\n");
        pl->vas_random = 1;
        max=rand()%x;
        if(pl->area != NULL){
            pl->area->_delete_game_area(pl->area);
            free(pl->area);
        }
        pl->area = area->_clone_area(area);
        area->_clone_move(get_pos[max],pl->move);

    }
    for (int i=0; i<x; i++){
        clon[i]->_delete_game_area(clon[i]);
        free(clon[i]);
        //free(clon[i]);
    }
    free(clon);
    for (int i=0; i<x; i++){
        free(get_pos[i]);
    }
    free(get_pos);
    return pl->move;
}
