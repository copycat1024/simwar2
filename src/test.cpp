#include <iostream>
#include <fstream>
#include "entity.h"
#include "hero.h"
#include "battle.h"
#include "config.h"

using std::cout;
using std::endl;
using std::ofstream;

void test_entity(void){
	LuaEntity e("test.lua");
	const int hp = 1;
	e.load(hp, "hp");
	cout << e[hp] << endl;
}

void test_hero(){
	SwHero h;
	cout << h[SwHeroKey::HP] << endl;
	cout << h[SwHeroKey::AD] << endl;
}

void test_simwar(){
}

void test_battle_hero(){
	ofstream file;
	file.open("battle_log.lua");

	SwBattle b(file, SIMWAR_EXECUTABLE_PATH);
}
