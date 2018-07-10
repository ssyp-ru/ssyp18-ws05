#pragma once
#include "engine.h"
#define E 0.1
#include <time.h>

typedef double(*get_value_fp)(struct game* game,void* data);
typedef void(*update_value_fp)(struct game* game_area, struct game* game1, void* data);
typedef void*(*getdata)(char*file);
typedef void(*savedata)(void* data,const char* file);

struct pl_st_agent{
    void* data;
    void* move;
    int vas_random;
    int fist_second;
    struct game* area;
    get_value_fp get_value;
    update_value_fp update_value;
    savedata _save_data_;
};
struct pl_st_agent* create_pl_st_agent(get_value_fp value, update_value_fp update,getdata get_data,savedata save_data,void* move_);
void delete_pl_st_agent(void* agent);
void* decide_move_agent(struct player* player_st,struct game* area);
