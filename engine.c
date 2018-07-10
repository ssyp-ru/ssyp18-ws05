#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

struct engine_state* create_engine(struct game* game_en, struct player* player1, struct player* player2)
{
    struct engine_state* list = (struct engine_state*) malloc(sizeof(struct engine_state));
    list->game = game_en;
    list->player_1 = player1;
    list->player_2 = player2;
    return list;
}
void delete_engine(void *engine)
{
    free(engine);
}
int run_engine(struct engine_state* engine)
{
    struct game* clon;
    struct game* clon1;
    void* move;
    void* move1;
    int win,over;
    engine->game->_print_this(engine->game);
    while(0<1){
        printf("while\n");
        clon = engine->game->_clone_area(engine->game);
        printf("cloned\n");
        move = engine->player_1->_decide_move(engine->player_1, clon);
        printf("decided\n");
        engine->game->_do_move(engine->game, move);
        engine->game->_print_this(engine->game);
        printf("moved\n");
        engine->game->_delete_game_area(clon);
        printf("freed\n");
        over = engine->game->_is_game_over(engine->game);
        if(over==1){
            win = engine->game->_get_vinner(engine->game);
            break;
        }
        clon1 = engine->game->_clone_area(engine->game);
        move1 = engine->player_2->_decide_move(engine->player_2, clon1);
        printf("decided\n");
        engine->game->_do_move(engine->game, move1);

        engine->game->_print_this(engine->game);
        printf("moved\n");
        engine->game->_delete_game_area(clon1);
        printf("freed\n");
        over=engine->game->_is_game_over(engine->game);
        if(over==1){
            win=engine->game->_get_vinner(engine->game);
            break;
        }
    }
    if(win!=2){
        printf("win %d\n",win);
    }else{
        printf("DRAW\n");
    }
    int result;
    if(win==0){
        result = 1;
    }else if(win==1){
        result = -1;
    }else{
       result = 0;
    }
    if(engine->player_1->inform_resultfunc != NULL){engine->player_1->inform_resultfunc(engine->player_1,result);}
    if(result != 0){
        result = result * -1;
    }
    if(engine->player_2->inform_resultfunc != NULL){engine->player_2->inform_resultfunc(engine->player_2,result);}

    return win;
    //engine->game->_delete_game_area(engine->game);
}
