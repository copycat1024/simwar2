#include "battle.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

Battle::Battle(){
	int i;
	_hero_pos = {1,3,4,5,7,0,1,2,4,7};
	for (i=0; i<5; i++){
		_hero_name[i] = "eklit";
	}
	for (i=5; i<10; i++){
		_hero_name[i] = "sora";
	}
	for (i=0; i<_hero_num; i++){
		_heros[i] = new Hero(this, i);
	}
	_log.push_back("pause()");
}

void Battle::run(){
	int turn = 0;
	while (!over()){
		_heros[turn]->turn();
		_log.push_back("pause()");
		turn++;
		if (turn>_hero_num-1) turn = 0;
	}
}

bool Battle::over(){
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

Log& Battle::get_log(){
	return _log;
}

void Battle::_write_log(string txt, int id){
	_log.push_back(txt);
}

void Battle::_invoke(int src, int tar, std::string state_name, int delta){
	_heros[tar]->_lua["hook"]["alter"](src, state_name, delta);
}

sol::table Battle::_map(int id){
	int i;
	sol::table res = _heros[id]->_lua.create_table();
	for (i=0;i<10;i++){
		res[i]=_hero_pos[i];
	}
	return res;
}
