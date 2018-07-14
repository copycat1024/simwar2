#include <iostream>
#include <exception>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "api.h"
#include "proxy.h"

#include "api_attack.h"

using std::cout;
using std::endl;
using simwar::Proxy;

typedef void (*simwar_func)(Proxy*, lua_State*);

template <simwar_func func>
int dispatch(lua_State* L){
	void** p = static_cast<void**>(lua_getextraspace(L));
	if (*p){
		Proxy* bat = static_cast<Proxy*>(*p);
		func(bat, L);
	} else {
		throw std::exception();
	}
}

namespace simwar {

	namespace api {
		void load(lua_State* L){
			lua_register(L, "simpleAttack", dispatch<simpleAttack>);
		}
	}

}
