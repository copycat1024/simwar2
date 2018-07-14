#include <iostream>

#include "battle.h"

using std::cout;
using std::endl;

namespace simwar{

	void Battle::init(const std::string& t0, const std::string& t1){
		team[0].init(t0);
		team[1].init(t1);
		active_team = 0;
		rotation = 0;
		result = BattleResult::NotOver;
	}

	void Battle::begin(){
		team[0].firstHero();
		team[1].firstHero();
		rotation = -1;
		next();
	}

	void Battle::next(){
		static const int turn_order[] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 1};

		if (over()) return;
		do {
			rotation++;
			if (rotation == 10){
				rotation = 0;
				team[0].firstHero();
				team[1].firstHero();
			}
			active_team = turn_order[rotation];
			team[active_team].nextHero();
		} while (team[active_team].active_hero > 4);
	}

	bool Battle::over(){
		if (team[0].lost()) result = BattleResult::TeamBWins;
		if (team[1].lost()) result = BattleResult::TeamAWins;
		return team[0].lost() || team[1].lost();
	}

	Team& Battle::getAllyTeam() {
		return team[active_team];
	}

	Team& Battle::getEnemyTeam() {
		return team[(active_team+1)%2];
	}

	Hero& Battle::getAlly(int id) {
		return getAllyTeam().heroes[id];
	}

	Hero& Battle::getEnemy(int id) {
		return getEnemyTeam().heroes[id];
	}

	Hero& Battle::getMyself() {
		Team& ally = getAllyTeam();
		if (ally.active_hero > 4) throw std::exception();
		if (ally.isDead(ally.active_hero)) throw std::exception();
		return ally.heroes[ally.active_hero];
	}
}
