#include "hero.h"
#include "battle.h"

using std::string;
using std::to_string;

void Hero::_load_api(){
	_lua["log"] = [this](string txt){
		this->_bat->_write_log(txt, this->_id);
	};
	_lua["invoke"] = [this](int tar, string state_name, int delta){
		this->_bat->_invoke(this->_id, tar, state_name, delta);
	};
	_lua["query"] = _lua.create_table();
	_lua["query"]["id"]  = [this]()->int{
		return this->_id;
	};
	_lua["query"]["map"] = [this]()->sol::table{
		return this->_bat->_map(this->_id);
	};
}

Hero::Hero(Battle* bat, int id){
	_bat = bat;
	_id = id;
	string name = bat->_hero_name[id];
	_lua.open_libraries(sol::lib::base);
	_load_api();
	_lua.script_file("hero/"+name+".lua");
    _lua["hook"]["init"]();
}

void Hero::turn(){
	_lua["hook"]["turn"]();
}

bool Hero::isDead(){
	return _lua["hook"]["dead"]();
}
