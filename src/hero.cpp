#include <iostream>
#include <string>
#include "hero.h"
#include "battle.h"

using std::endl;
using std::cout;
using std::string;

// helper functions
int order(int my_pos, int enemy_pos){
    int h = enemy_pos%3;
    int l = (enemy_pos-h)/3;
    int m = my_pos%3;
    if (m==2) h = 2-h;
    if (m==1) h = (4-h)%3;
    return l+h*3;
}

// class SwHero definition

inline EntityValue& SwHero::operator[](SwHeroKey k){
	return Entity::operator[]((EntityKey) k);
}

inline void SwHero::alter(SwHeroKey k, EntityValue v){
	Entity::alter((EntityKey) k, v);
}

// class SwBattleHero definition

// -private methods

// --locate hero file, return filename and path
inline const string SwBattleHero::_locateHeroFile(SwBattle* bat, int id){
	std::string path = bat->_hero_path+bat->_hero_name[id]+".lua";
	return path;
}

// --log alter call
inline void SwBattleHero::_logAlter(SwHeroKey k, EntityValue v){
	_bat->log << "alter(";
	_bat->log << (*this)[SwHeroKey::ID] << ","; // id
	_bat->log << (EntityKey) k; // key
	_bat->log << "," << v; // delta
	_bat->log << ")" << endl;
}

// --load data from lua
void SwBattleHero::_load(SwHeroKey k, const char* varname){
	LuaEntity::load((EntityKey)k, varname);
    if (_bat->write_log) _logAlter(k, (*this)[k]);
}

// --load data from lua
void SwBattleHero::_alter(SwHeroKey k, EntityValue v){
	SwHero::alter(k, v);
	if (_bat->write_log) _logAlter(k, v);
}

int SwBattleHero::_targetSingle(){
	int td = ((this->id()/5+1)%2)*5; // enemy team delta
	int i;
	int m = (*this)[SwHeroKey::PS]; // my position
	int ei, et; // enemy position
    int t = 0; // target
	while (_bat->_heros[t+td]->isDead()){
		t++;
	}
	for (i=t+1; i<5; i++){
		ei = _bat->_hero_pos[i+td];
		et = _bat->_hero_pos[t+td];
		if (order(m,ei) < order(m,et) && !_bat->_heros[i+td]->isDead()){
			t = i;
		}
	}
	return t+td;
}

// -public methods

// --constructor
SwBattleHero::SwBattleHero(SwBattle* bat, int id) : LuaEntity(_locateHeroFile(bat, id)){
	_bat = bat;

	// load battle info from bat
	(*this)[SwHeroKey::ID] = id;
	(*this)[SwHeroKey::PS] = _bat->_hero_pos[id];

    // log hero initial state
	if (bat->write_log){
		bat->log << "init_hero(";
		bat->log << id << ","; // id
		bat->log << "'" << _bat->_hero_name[id] << "'"; // name
		bat->log << "," << (*this)[SwHeroKey::PS]; // postition
		bat->log << ")" << endl;
	}

	// load config info from lua file
	SwBattleHero::_load(SwHeroKey::HP, "hp");
	SwBattleHero::_load(SwHeroKey::AD, "ad");

}

void SwBattleHero::turn(){
	int target = _targetSingle();
	_bat->_heros[target]->_alter(SwHeroKey::HP, -(*this)[SwHeroKey::AD]);
}
