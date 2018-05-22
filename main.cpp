#include <fstream>
#include "battle.h"

using std::ofstream;

int main(void){
	Battle b;
	b.run();
	ofstream file;

	file.open("battle_log.lua");
	for (auto t : b.get_log()){
		file << t << '\n';
	}
	return 0;
}
