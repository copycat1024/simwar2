#include <iostream>
#include <string>
#include "battle.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

SwBattle::SwBattle(SwLogStream& l, const char* hero_path, const char* team_a_path, const char* team_b_path):log(l), _hero_path(hero_path){
	int team_id;
	auto load_pos = [this, &team_id](int p1, int p2, int p3, int p4, int p5){
		this->_hero_pos[team_id + 0] = p1;
		this->_hero_pos[team_id + 1] = p2;
		this->_hero_pos[team_id + 2] = p3;
		this->_hero_pos[team_id + 3] = p4;
		this->_hero_pos[team_id + 4] = p5;
	};
	auto load_hero = [this, &team_id](string h1, string h2, string h3, string h4, string h5){
		this->_hero_name[team_id + 0] = h1;
		this->_hero_name[team_id + 1] = h2;
		this->_hero_name[team_id + 2] = h3;
		this->_hero_name[team_id + 3] = h4;
		this->_hero_name[team_id + 4] = h5;
	};
	sol::state t1, t2;

	// team 1
	team_id = 0;
	t1["load_pos"] = load_pos;
	t1["load_hero"] = load_hero;
	t1.script_file(team_a_path);

	// team 2
	team_id = 5;
	t2["load_pos"] = load_pos;
	t2["load_hero"] = load_hero;
	t2.script_file(team_b_path);

	// load heroes
	int i;
	log << "init_start()" << endl;
	for (i=0; i<_hero_num; i++){
		_heros[i] = new SwBattleHero(this, i);
	}
	log << "init_end()" << endl;
}

SwBattle::~SwBattle(){
	for (auto h: _heros){
		delete h;
	}
}

void SwBattle::run(){
	int turn = 0;
	while (!over()){
		if (!_heros[turn]->isDead()){
			log << "turn_start(" << turn << ")" << endl;
			_heros[turn]->turn();
			log << "turn_end()" << endl;
		}
		turn++;
		if (turn>_hero_num-1) turn = 0;
	}
}

bool SwBattle::over(){
	bool t0 = true;
	for (int i=0; i<5; i++){
		t0 &= _heros[i]->isDead();
	}
	bool t1 = true;
	for (int i=5; i<10; i++){
		t1 &= _heros[i]->isDead();
	}
	if (t0) winner = 1;
	if (t1) winner = 0;
	return t0 || t1;
}
