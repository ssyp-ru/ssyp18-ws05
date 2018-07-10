#pragma once
struct player;
struct game;

typedef void*(*create)();
typedef void (*delete_p)(void* d);
typedef void*(*decide)(struct player* player_st,struct game* area);
typedef void(*inform_result_func)(struct player* player_st,int  result);

typedef void (*delete_g)(struct game* d);
typedef int(*ispossible)(struct game* area, void* move1);
typedef int(*getvinner)(struct game* area);
typedef int (*isgameover)(struct game*area);
typedef void (*domove)(struct game* area,void* move1);
typedef void (*printg)(struct game* area);
typedef struct game* (*clonearea)(struct game* area);
typedef void** (*getmoves)(struct game* area, int* length);
typedef void(*clon_move)(void* move_input,void* move_output);

struct player{
     //create _create_player_st;
     inform_result_func inform_resultfunc;
     delete_p _delete_player_st;
     decide _decide_move;
     void* players;
};

struct game{
    create _create_game_area;
    delete_g _delete_game_area;
    ispossible _is_possible;
    getvinner _get_vinner;
    isgameover _is_game_over;
    domove _do_move;
    printg _print_this;
    clonearea _clone_area;
    getmoves _get_moves;
    clon_move _clone_move;
    void* area;
};

struct engine_state{
    struct game* game;
    struct player* player_1;
    struct player* player_2;
};

struct engine_state* create_engine(struct game* game_en, struct player* player1, struct player* player2);
void delete_engine(void* engine);
int run_engine(struct engine_state* engine);
