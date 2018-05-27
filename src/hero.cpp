#include <iostream>
#include "hero.h"
#include "battle.h"

using std::endl;

// class SwHero definition

EntityValue& SwHero::operator[](SwHeroKey k){
	return Entity::operator[]((EntityKey) k);
}

EntityValue SwHero::hp(){
	return (*this)[SwHeroKey::HP];
}

// class SwBattleHero definition


// -private methods

// --load data from lua
void SwBattleHero::_load(SwHeroKey k, const char* varname){
	LuaEntity::load((EntityKey)k, varname);
}

// --locate hero file, return filename and path
inline const char* SwBattleHero::_locateHeroFile(SwBattle* bat, int id){
	return ("hero/"+bat->_hero_name[id]+".lua").c_str();
}

// -public methods

// --constructor
SwBattleHero::SwBattleHero(SwBattle* bat, int id) : LuaEntity(_locateHeroFile(bat, id)){
	// load battle info from bat
	(*this)[SwHeroKey::ID] = id;
	(*this)[SwHeroKey::PS] = bat->_hero_pos[id];

	// load config info from lua file
	SwBattleHero::_load(SwHeroKey::HP, "hp");
	SwBattleHero::_load(SwHeroKey::AD, "ad");

    // log hero initial state
	bat->log << "init_hero(";
	bat->log << id << ","; // id
	bat->log << "'" << bat->_hero_name[id] << "'"; // name
	bat->log << "," << (*this)[SwHeroKey::PS]; // postition
	bat->log << "," << (*this)[SwHeroKey::HP]; // hit point
	bat->log << ")" << endl;
}
