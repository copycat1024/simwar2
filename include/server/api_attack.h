#ifndef SW_API_ATTACK_H
#define SW_API_ATTACK_H

extern "C" {
#include "lua.h"
}

namespace simwar {

	class Proxy;

	namespace api {
		void simpleAttack(Proxy* prx, lua_State* L);
	}

}

#endif
