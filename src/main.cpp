#include <fstream>
#include <iostream>
#include "client.h"
#include "test.h"
#include "battle.h"

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
	SwBattle b(file);
//	b.run();

	SwClient c("battle_log.lua");
	c.show();
}
