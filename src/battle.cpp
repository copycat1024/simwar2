#include <iostream>
#include <string>
#include "battle.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

SwBattle::SwBattle(SwLogStream& l):log(l){
	// default init
	int i;
	_hero_pos = {1,3,4,5,7,0,1,2,4,7};
	for (i=0; i<5; i++){
		_hero_name[i] = "eklit";
	}
	for (i=5; i<10; i++){
		_hero_name[i] = "sora";
	}

	log << "init_start()" << endl;
	// load heroes
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
	return t0 || t1;
}
