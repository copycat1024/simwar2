#include <fstream>
#include "battle.h"
#include "client.h"

using std::ofstream;

int main(void){
	Battle b;
	Client c("battle_log.lua");
	b.run();
	ofstream file;

	file.open("battle_log.lua");
	for (auto t : b.get_log()){
		file << t << '\n';
	}
	c.show();
	return 0;
}
