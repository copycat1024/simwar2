#ifndef SW_BATTLE_H
#define SW_BATTLE_H

#include <string>
#include <array>
#include "team.h"

namespace simwar{

	namespace BattleResult {
		static const int NotOver = 0;
		static const int TeamAWins = 1;
		static const int TeamBWins = 2;
	}

	struct Battle {
		void init(const std::string&, const std::string&);
		void begin();
		void next();
		bool over();

		Team& getAllyTeam();
		Team& getEnemyTeam();

		Hero& getAlly(int id);
		Hero& getEnemy(int id);
		Hero& getMyself();

		std::array<Team, 2> team;
		int active_team;
		int rotation;
		int result;
	};

}

#endif
