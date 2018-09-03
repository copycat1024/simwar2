#ifndef SW_TEAM_H
#define SW_TEAM_H

#include <string>
#include <array>
#include "entity.h"
#include "combi/model.h"

namespace simwar {

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
