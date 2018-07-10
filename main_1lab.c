#include <stdio.h>
#include <stdlib.h>

#include "game_lab.h"
#include "player_lab.h"

int lab_main()
{
   /* create_player_state();
	while (true)
	{
		struct player_stats *player = (struct player_stats*) create_player_state();
		struct player_stats *ai = (struct player_stats*) create_player_state();
		struct gmove *plmove;
		struct game_area *area = (struct game_area*) create_area();
		print_area(area);
		while (true)
		{
			plmove = (struct gmove*) decide_move_pl(player, area);
			do_move(area, plmove);
			if (qgame_over(area)==1)
				break;
			do_move(area, decide_move_ai(ai, area));
			if (qgame_over(area) == 1)
				break;
			print_area(area);

		}

	}*/
	return 0;
}
