#include <fstream>
#include <iostream>
#include "client.h"
#include "test.h"
#include "battle.h"
#include "config.h"

using std::ofstream;
using std::cout;
using std::endl;

void real_main(void);

int main(void){
//	test_battle_hero();
	real_main();
}

void real_main(void){
	ofstream file;
	file.open("battle_log.lua");
	SwBattle b(file, DEFAULT_HERO_PATH);
	b.run();

	SwClient c("battle_log.lua", CLIENT_LUA_PATH);
	c.show();
}
