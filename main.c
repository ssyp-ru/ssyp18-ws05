#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"
#include "game_kn15_15.h"
#include "player_kn15_15.h"
#include "game_lab.h"
#include "player_lab.h"
#include "game_krestNol.h"
#include "player_krestNol.h"
#include "game_kings.h"
#include "players_kings.h"

int main()
{
    printf("hello\n");
    srand(time(NULL));

    //крестики-нолики
    //_create_player_2();//lab_create_player2();
    //printf("players created\n");
    /*
    for(int i=0;i<10000;i++){
        struct game* game = krno_create_game();
        printf("game created\n");
        struct player* player1 = krno_creat_pl_agent();
        struct player* player2 = krno_creat_pl_agent_2(player1);

        struct engine_state* engine = create_engine(game, player1, player2);
        printf("engine created\n");
        run_engine(engine);
        delete_engine(engine);

        krno_delete_player(player1);
        krno_delete_player(player2);
        krno_delete_game(game);
    }*/

    struct game* game = krno_create_game();
    struct player* player2 = krno_creat_pl_agent();
    struct player* player1 = krno_create_player();

    struct engine_state* engine = create_engine(game, player1, player2);
    printf("engine created\n");
    run_engine(engine);
    delete_engine(engine);

    krno_delete_player(player1);
    krno_delete_player(player2);
    krno_delete_game(game);/*/

    /*struct game* game = krno_create_game();
    printf("game created\11n");
    struct player* player1 = krno_creat_pl_agent();
    struct player* player2 = krno_create_player();//_create_player_2();//lab_create_player2();
    printf("players created\n");
    struct engine_state* engine = create_engine(game, player1, player2);
    printf("engine created\n");
    run_engine(engine);
    delete_engine(engine);

    printf("delete_engine\n");

    krno_delete_player(player1);
    krno_delete_player(player2);
    krno_delete_game(game);*/


    //Лабиринт
    /*
    struct game* game = lab_create_game();
    struct player* player1 = lab_create_player();
    struct player* player2 = lab_create_player2();

    struct engine_state* engine = create_engine(game, player1, player2);
    printf("engine created\n");
    run_engine(engine);
    delete_engine(engine);

    lab_delete_player(player1);
    lab_delete_player(player2);
    lab_delete_game(game);
*/


    //крестики-нолики 15х15

    //Обучение
/*
    for(int i=0;i<100000;i++){
        struct game* game = kn15_15_create_game();
        struct player* player1 = kn15_create_player_agent();
        struct player* player2 = kn15_create_player_agent_2(player1);

        struct engine_state* engine = create_engine(game, player1, player2);
        printf("engine created\n");
        run_engine(engine);
        delete_engine(engine);

        kn_15_15_delete_player(player1);
        kn_15_15_delete_player(player2);
    }
*/
    /*
    //Позорное поражение рандому
    int wins_agent = 0, wins_random = 0;
    for(int i=0;i<10;i++){
        struct game* game = kn15_15_create_game();
        struct player* player1 = kn15_create_player_agent();
        struct player* player2 = kn_15_15_create_player_random();//kn15_create_player_agent_2(player1);

        struct engine_state* engine = create_engine(game, player1, player2);
        printf("engine created\n");
        int win = run_engine(engine);
        if(win == 0) wins_agent++;
        if(win == 1) wins_random++;
        delete_engine(engine);

        kn_15_15_delete_player(player1);
        kn_15_15_delete_player(player2);

        //--------

        game = kn15_15_create_game();
        player2 = kn15_create_player_agent();
        player1 = kn_15_15_create_player_random();//kn15_create_player_agent_2(player1);

        engine = create_engine(game, player1, player2);
        printf("engine created\n");
        win = run_engine(engine);
        if(win == 0) wins_random++;
        if(win == 1) wins_agent++;
        delete_engine(engine);

        kn_15_15_delete_player(player1);
        kn_15_15_delete_player(player2);
    }

    printf("agent: %d; random: %d", wins_agent, wins_random);
    */

/*
    //Расстановка королей
    struct game* game = kings_create_game();
    struct player* player1 = kings_create_random_player();
    struct player* player2 = kings_create_choosebot_player();

    struct engine_state* engine = create_engine(game, player1, player2);
    printf("engine created\n");
    run_engine(engine);
    delete_engine(engine);

    kings_delete_player(player1);
    kings_delete_player(player2);*/

    return 0;
}
