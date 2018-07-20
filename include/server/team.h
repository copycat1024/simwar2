#ifndef SW_TEAM_H
#define SW_TEAM_H

#include <string>
#include <array>
#include "entity.h"

namespace simwar {

	struct TeamSetup {
		std::array<int, 5> formation;
		std::array<int, 5> heroes;		
	};

	struct Team {
		void init(const std::string&);
		bool isDead(int) const;
		bool lost() const;
		void firstHero();
		void nextHero();

		TeamSetup setup;
		std::array<Hero, 5> heroes;
		int active_hero;
	};

}

#endif
