#ifndef SW_BATTLE_H
#define SW_BATTLE_H

#include <string>
#include <array>
#include "team.h"

namespace simwar{

	struct BattleModel{
		void init(const std::string&, const std::string&);

		std::array<Team, 2> team;
		int active_team;
		int rotation;
	};

}

#endif
