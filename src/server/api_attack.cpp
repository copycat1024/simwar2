#include <iostream>
#include <exception>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "api.h"
#include "proxy.h"

using std::cout;
using std::endl;
using namespace simwar;

int order(int my_pos, int enemy_pos){
    int h = enemy_pos%3;
    int l = (enemy_pos-h)/3;
    int m = my_pos%3;
    if (m==2) h = 2-h;
    if (m==1) h = (4-h)%3;
    return l+h*3;
}

int targetSingle(Proxy* prx){
	Battle& bat = prx->battle;
	int i;
	int m = bat.getMyself().at(Key::Pos); // my position
	int ei, et; // enemy position
    int t = 0; // target
	while (bat.getEnemyTeam().isDead(t)){
		t++;
	}
	for (i=t+1; i<5; i++){
		ei = bat.getEnemyTeam().setup.formation[i];
		et = bat.getEnemyTeam().setup.formation[t];
		if (order(m,ei) < order(m,et) && !bat.getEnemyTeam().isDead(i)){
			t = i;
		}
	}
	return t;
}

namespace simwar {

	namespace api {

		void simpleAttack(Proxy* prx, lua_State* L){
			int target = targetSingle(prx);
			int damage = prx->battle.getMyself()[Key::AD];
			prx->alterEnemy(target, Key::HP, -damage);
		}

	}

}
