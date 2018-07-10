#include "battle.h"

namespace simwar{

	void Battle::init(const std::string& t0, const std::string& t1){
		team[0].init(t0);
		team[1].init(t1);
		active_team = 0;
		rotation = 0;
	}

	void Battle::next(){
		int turn_order[] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
		do {
			rotation++;
			if (rotation == 10){
				rotation = 0;
				team[0].firstHero();
				team[1].firstHero();
			}
			active_team = turn_order[rotation];
			team[active_team].nextHero();
		} while (team[active_team].active_hero < 5);
	}

}
