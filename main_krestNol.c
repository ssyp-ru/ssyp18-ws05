#include "game_krestNol.h"
#include "player_krestNol.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int krestNol_main()
{
	/*srand(time(NULL));

	int x=0;
	int g=0;
	struct game_sost* t;
	struct player_state* pl1;
	struct player_state* pl2;
	t = (struct game_sost*)creat_dor();

	pl1 = (struct player_state*) create_pl();
	pl2 = (struct player_state*) create_pl();

    int c=-1;
	while (0<1)
	{
	    c=0;
        while(c!=1){
			c = prov(t,pl_1_decide(pl1,t));
		}
		t->l=1;
        make_xod(t,((struct player_state*)pl1)->m);

        x=get_winner(t);
        g=is_gameover(t);

		if (x==1){
			break;
		}else if((g==0)&&(x==0)){
			break;
		}

		t->l=2;
        make_xod(t,pl_2_decide(pl2,t));

		x=get_winner(t);
        g=is_gameover(t);

		write(t);

		if (x==2){
			break;
		}else if((g==0)&&(x==0)){
			break;
		}
	}
	if (x==3) {
        write(t);
		printf("DRAW\n");
		de_te(t);
		return 0;
	}
	write(t);
	printf("win %d\n",x);
	de_te(t);*/
	return 0;
}
