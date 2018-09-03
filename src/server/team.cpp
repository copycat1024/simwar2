#include <string>
#include <iostream>
#include <exception>

#include "team.h"
#include "entity.h"
#include "errors.h"
#include "combi.h"

using std::string;
using std::cout;
using std::endl;

namespace simwar{

	void Team::init(const string& stamp){

		// get team setup from stamp + check
		setup = stampToSetup(stamp);

		// load heroes' basic stats
		for (int i=0; i<5; i++){
			heroes[i][Key::ID]  = i;
			heroes[i][Key::HID] = setup.heroes[i];
			heroes[i][Key::Pos] = setup.formation[i];
		}

	}

	bool Team::isDead(int i) const{
		if (i>4 || i<0) return true;
		return heroes[i].at(Key::HP) <= 0;
	}

	bool Team::lost() const{
		for (int i=0; i<5; i++){
			if (!isDead(i)) return false;
		}
		return true;
	}

	void Team::nextHero(){
		do {
			active_hero++;
		} while (active_hero<5 && isDead(active_hero));
	}

	void Team::firstHero(){
		active_hero = -1;
	}
}
