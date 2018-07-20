#include <iostream>
#include "proxy.h"

using std::cout;
using std::endl;

namespace simwar {

	Proxy::Proxy(const Director& dir): _dir(dir), log(0){
	}

	int Proxy::run_battle(const std::string& ta, const std::string& tb){
		battle.init(ta, tb);
		_load_roles();
		if (log) log->init(battle);
		battle.begin();

		if (log) log->start("run");
		do {
			if (log) {
				int team = battle.active_team;
				int hero = battle.team[team].active_hero;
				log->turn(team, hero);
			}
			_call_roles();
			battle.next();
		} while (battle.result == BattleResult::NotOver);
		if (log) log->end();

		if (log) log->info();

		return battle.result;
	}

	void Proxy::alterAlly(int hero, HeroKey key, HeroValue val){
		_alter(battle.active_team, hero, key, val);
	}

	void Proxy::alterEnemy(int hero, HeroKey key, HeroValue val){
		_alter((battle.active_team+1)%2, hero, key, val);
	}

	void Proxy::setAlly(int hero, HeroKey key, HeroValue val){
		_set(battle.active_team, hero, key, val);
	}

	void Proxy::setEnemy(int hero, HeroKey key, HeroValue val){
		_set((battle.active_team+1)%2, hero, key, val);
	}

	void Proxy::_load_roles(){
		int i, j;
		const auto& roles = _dir.hero_roles();

		for (i=0; i<2; i++){
			for (j=0; j<5; j++){
				Hero& hero = battle.team[i].heroes[j];
				if (hero[Key::HID] >= roles.size()) throw std::exception();
				hero[Key::HP] = roles[hero.at(Key::HID)].get("hp");
				hero[Key::AD] = roles[hero.at(Key::HID)].get("ad");
			}
		}
	}

	void Proxy::_call_roles(){
		int hid = battle.getMyself().at(Key::HID);
		const Role& r = _dir.hero_roles().at(hid);

		r.setProxy(this);
		r.call("turn");
		r.setProxy(0);
	}

	void Proxy::_alter(int team, int hero, HeroKey key, HeroValue val){
		battle.team[team].heroes[hero][key] += val;
		if (log) log->alter(team, hero, key, val);
	}

	void Proxy::_set(int team, int hero, HeroKey key, HeroValue val){
		battle.team[team].heroes[hero][key] = val;
		if (log) log->set(team, hero, key, val);
	}

}
